#include "Client.h"

Client::Client(char *server_ip) {
    port = 8848;

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
                    if (exist(source + "/" + std::string(dp->d_name)) == 'n') {
                        request_service("filecpy " + source + "/" + std::string(dp->d_name));
                        send_file(source + "/" + std::string(dp->d_name));
                    }
                } else {
                    backup(source + "/" + std::string(dp->d_name));
                }
            }
            closedir(d);
        } else if (s.st_mode & S_IFREG) {
            if (exist(source) == 'n') {
                request_service("filecpy " + source);
                send_file(source);
            }
        }
    } else {
        std::cerr << "[ERROR] Cannot access " << source << ": " << strerror(errno) << std::endl;
    }
}


void Client::receive_file(const std::string& filepath) {
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
    char buffer[SIZE] = {0};
    FILE *fp;
    fp = fopen(filepath.c_str(), "wb");
    int nCount;
    while((nCount = recv(sockfd, buffer, SIZE, 0)) > 0 ){
        fwrite(buffer, nCount, 1, fp);
    }
    std::cout << "[CLIENT] Data written in the file successfully." << std::endl;
    std::cout << "[CLIENT] Closing the connection." << std::endl;
    close(sockfd);
    fflush(fp);
}

void Client::monitor(const std::string& source) {
    struct stat s;
    if (stat(source.c_str(), &s) == 0) {
        struct stat last_s = s;
        while(true) {
            stat(source.c_str(), &s);
            if(s.st_size > last_s.st_size) {
                backup(source);
            }
            last_s = s;
            sleep(5);
        }
    } else {
        std::cerr << "[ERROR] Cannot access " << source << ": " << std::strerror(errno) << std::endl;
    }
}


char Client::exist(const std::string& filepath) {
    request_service("exist " + filepath);
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
    char buffer = {0};
    recv(sockfd, &buffer, SIZE, 0);
    return buffer;
}
