#ifndef NEWSERVER_SERVER_H
#define NEWSERVER_SERVER_H
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <string>
#include <dirent.h>
#define SIZE 1024

class Server {
private:
    int port, clientport;
    int e;

    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;

public:
    Server();
    int make_dirs(const char *dir);
    void service();
    void receive_file(const std::string& filepath);
    void send_file(const std::string& filepath);
    void create_dir(const std::string& dirpath);
    void request_service(const std::string& service);
    void restore(const std::string& source);
};


#endif //NEWSERVER_SERVER_H
