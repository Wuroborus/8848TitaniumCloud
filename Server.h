#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H
#include <iostream>
#include <fstream>
#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <cstdlib>
#include <netinet/in.h>
#include <arpa/inet.h>

class Server {
private:
    int PORT;

    int general_socket_descriptor;
    int new_socket_descriptor;

    struct sockaddr_in address;
    int address_length;

public:
    Server();
    void create_socket();
    void bind_socket();
    void set_listen();
    void accept_requests();
    void send_file(std::string path);
    void receive_file(std::string path);
};


#endif //SERVER_SERVER_H
