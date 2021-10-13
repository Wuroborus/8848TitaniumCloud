#include "Server.h"

int Server::make_dirs(const char *dir)
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

Server::Server() {
    port = 8848;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        std::cerr << "[ERROR] Error in socket: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "[SERVER] Socket created successfully." << std::endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = INADDR_ANY;

    e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
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
    addr_size = sizeof(new_addr);
}

void Server::service() {
    new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
    char buffer[SIZE] = {0};
    recv(new_sock, buffer, SIZE, 0);
    buffer[SIZE] = '\0';
    std::cout << "[SERVER] Requested to " << buffer << std::endl;
    std::cout << "[SERVER] Closing the connection." << std::endl;
    close(new_sock);
    if (buffer[0] == 'f') {
        receive_file(buffer + 8);
    } else if (buffer[0] == 'd') {
        create_dir(buffer + 7);
    } else if (buffer[0] == 'r') {
        send_file(buffer + 9);
    } else if (buffer[0] == 'e') {
        exist(buffer + 6);
    }
}

void Server::receive_file(const std::string& filepath) {
    std::string::size_type idx = filepath.rfind('/', filepath.length());
    std::string par_dir = filepath.substr(0, idx);
    if (access(("./backup" + par_dir).c_str(), 00) == -1) {
        std::cout << "[SERVER] Creating directory." << std::endl;
        if (make_dirs(("./backup" + par_dir).c_str()) == -1) {
            std::cerr << "[ERROR] Directory creation failed: " << strerror(errno) << std::endl;
        }
    }
    new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
    char buffer[SIZE] = {0};
    FILE *fp;
    fp = fopen(("./backup" + filepath).c_str(), "wb");
    int nCount;
    while((nCount = recv(new_sock, buffer, SIZE, 0)) > 0 ){
        fwrite(buffer, nCount, 1, fp);
    }
    std::cout << "[SERVER] Data written in the file successfully." << std::endl;
    std::cout << "[SERVER] Closing the connection." << std::endl;
    close(new_sock);
    fflush(fp);
    service();
}

void Server::create_dir(const std::string& dirpath) {
    std::string::size_type idx = dirpath.rfind('/', dirpath.length());
    std::string par_dir = dirpath.substr(0, idx);
    if (access(("./backup" + par_dir).c_str(), 00) == -1) {
        std::cout << "[SERVER] Creating directory." << std::endl;
        if (make_dirs(("./backup" + par_dir).c_str()) == -1) {
            std::cerr << "[ERROR] Directory creation failed: " << strerror(errno) << std::endl;
        }
    }
    make_dirs(("./backup" + dirpath).c_str());
    std::cout << "[SERVER] Directory created." << std::endl;
    service();
}

void Server::send_file(const std::string &filepath) {
    new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
    FILE *fp;
    fp = fopen(("./backup" + filepath).c_str(), "rb");
    if (fp == NULL) {
        std::cerr << "[ERROR] Error in reading file: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    char data[SIZE] = {0};
    int nCount;
    while((nCount = fread(data, 1, SIZE, fp)) > 0) {
        if (send(new_sock, data, nCount, 0) == -1) {
            std::cerr << "[ERROR] Error in sending file: " << strerror(errno) << std::endl;
            exit(EXIT_FAILURE);
        }
        bzero(data, SIZE);
    }
    std::cout << "[SERVER] File sent successfully." << std::endl;

    std::cout << "[SERVER] Closing the connection." << std::endl;
    close(new_sock);
    service();
}

void Server::exist(const std::string& filepath) {
    new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
    std::string data;
    if (access(("./backup" + filepath).c_str(), 00) == -1) {
        data = "n";
    } else {
        data = "e";
    }
    send(new_sock, data.c_str(), data.length(), 0);
    close(new_sock);
    service();
}
