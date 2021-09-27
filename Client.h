#ifndef NEWCLIENT_CLIENT_H
#define NEWCLIENT_CLIENT_H
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <dirent.h>
#define SIZE 1024


class Client {
private:
    int port;
    int e;
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t addr_size;

public:
    Client(char *server_ip);
    void request_service(const std::string& service);
    void send_file(const std::string& filepath);
    void backup(const std::string& source);
    void receive_file(const std::string& filepath);
    void restore(const std::string& dest);

    void service();

    void create_dir(const std::string &dirpath);
    void monitor(const std::string& source);
    char exist(const std::string& filepath);
};


#endif //NEWCLIENT_CLIENT_H
