#include "Client.h"

int Client::make_dirs(const char *dir)
{
    if(NULL == dir || '\0' == *dir)
        return -1;

    const char *p = strrchr(dir, '/');
    if(p != NULL)
    {
        char parent_dir[4096] = { 0 };
        strncpy(parent_dir, dir, p - dir);
        if(access(parent_dir, F_OK) != 0)
            make_dirs(parent_dir);
    }

    if(access(dir, F_OK) != 0)
    {
        if( mkdir(dir, 0777) != 0)
            return -1;
    }
    return 0;
}

Client::Client(char *server_ip) {
    port = 8848;
    clientport = 8849;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
}

void Client::request_service(const std::string& service) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        std::cerr << "[ERROR] Error in socket: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "[CLIENT] Socket created successfully." << std::endl;
    e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(e == -1) {
        std::cerr << "[ERROR] Error in socket: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "[CLIENT] Connected to Server." << std::endl;
    send(sockfd, service.c_str(), service.length(), 0);
    std::cout << "[CLIENT] Requested server to " << service << std::endl;
    std::cout << "[CLIENT] Closing the connection." << std::endl;
    close(sockfd);
}

void Client::send_file(const std::string& filepath) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        std::cerr << "[ERROR] Error in socket: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "[CLIENT] Socket created successfully." << std::endl;
    e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(e == -1) {
        std::cerr << "[ERROR] Error in socket: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "[CLIENT] Connected to Server." << std::endl;

    FILE *fp;

    fp = fopen(filepath.c_str(), "rb");
    if (fp == NULL) {
        std::cerr << "[ERROR] Error in reading file: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    char data[SIZE] = {0};
    int nCount;
    while((nCount = fread(data, 1, SIZE, fp)) > 0) {
        if (send(sockfd, data, nCount, 0) == -1) {
            std::cerr << "[ERROR] Error in sending file: " << strerror(errno) << std::endl;
            exit(EXIT_FAILURE);
        }
        bzero(data, SIZE);
    }
    std::cout << "[CLIENT] File sent successfully." << std::endl;

    std::cout << "[CLIENT] Closing the connection." << std::endl;
    close(sockfd);
}

void Client::backup(const std::string& source) {
    struct stat s;
    if (stat(source.c_str(), &s) == 0) {
        if (s.st_mode & S_IFDIR) {
            request_service("dircpy " + source);
            DIR *d = NULL;
            struct dirent *dp = NULL;
            struct stat st;

            if(!(d = opendir(source.c_str()))) {
                std::cerr << "[ERROR] Error in opening directory: " << strerror(errno) << std::endl;
            }
            while((dp = readdir(d)) != NULL) {
                if((!strncmp(dp->d_name, ".", 1)) || (!strncmp(dp->d_name, "..", 2)))
                    continue;
                stat(source.c_str(), &st);
                if(!S_ISDIR(st.st_mode)) {
                    request_service("filecpy " + source + "/" + std::string(dp->d_name));
                    send_file(source + "/" + std::string(dp->d_name));
                } else {
                    backup(source + "/" + std::string(dp->d_name));
                }
            }
            closedir(d);
        } else if (s.st_mode & S_IFREG) {
            request_service("filecpy " + source);
            send_file(source);
        }
    } else {
        std::cerr << "[ERROR] Cannot access " << source << ": " << strerror(errno) << std::endl;
    }
}

void Client::service() {
    new_sock = accept(sockfd, (struct sockaddr*)&server_addr, &addr_size);
    char buffer[SIZE] = {0};
    recv(new_sock, buffer, SIZE, 0);
    buffer[SIZE] = '\0';
    std::cout << "[CLIENT] Requested to " << buffer << std::endl;
    std::cout << "[CLIENT] Closing the connection." << std::endl;
    close(new_sock);
    if (buffer[0] == 'f') {
        receive_file(buffer + 8);
    } else if (buffer[0] == 'd') {
        create_dir(buffer + 7);
    }
}

void Client::create_dir(const std::string& dirpath) {
    std::string::size_type idx = dirpath.rfind('/', dirpath.length());
    std::string par_dir = dirpath.substr(0, idx);
    if (access(("./backup" + par_dir).c_str(), 00) == -1) {
        std::cout << "[CLIENT] Creating directory." << std::endl;
        if (make_dirs(("./backup" + par_dir).c_str()) == -1) {
            std::cerr << "[CLIENT] Directory creation failed: " << strerror(errno) << std::endl;
        }
    }
    make_dirs(("./backup" + dirpath).c_str());
    std::cout << "[CLIENT] Directory created." << std::endl;
    service();
}

void Client::receive_file(const std::string& filepath) {
    std::string::size_type idx = filepath.rfind('/', filepath.length());
    std::string par_dir = filepath.substr(0, idx);
    if (access(par_dir.c_str(), 00) == -1) {
        std::cout << "[CLIENT] Creating directory." << std::endl;
        if (make_dirs(par_dir.c_str()) == -1) {
            std::cerr << "[ERROR] Directory creation failed: " << strerror(errno) << std::endl;
        }
    }
    new_sock = accept(sockfd, (struct sockaddr*)&server_addr, &addr_size);
    char buffer[SIZE] = {0};
    FILE *fp;
    fp = fopen(filepath.c_str(), "wb");
    int nCount;
    while((nCount = recv(new_sock, buffer, SIZE, 0)) > 0 ){
        fwrite(buffer, nCount, 1, fp);
    }
    std::cout << "[CLIENT] Data written in the file successfully." << std::endl;
    std::cout << "[CLIENT] Closing the connection." << std::endl;
    close(new_sock);
    fflush(fp);
    service();
}

void Client::restore(const std::string& dest) {
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = clientport;
    client_addr.sin_addr.s_addr = INADDR_ANY;

    e = bind(sockfd, (struct sockaddr*)&client_addr, sizeof(client_addr));
    if(e < 0) {
        std::cerr << "[ERROR] Error in bind: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "[SERVER] Binding successful." << std::endl;

    if(listen(sockfd, 10) == 0){
        std::cout << "[SERVER] Listening..." << std::endl;
    }else{
        std::cerr << "[ERROR] Error in listening: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    addr_size = sizeof(server_addr);
    request_service("restore " + dest);
    service();
}
