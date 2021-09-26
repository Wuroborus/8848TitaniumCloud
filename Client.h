#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H
#include <iostream>
#include <fstream>
#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <cstdlib>
#include <netinet/in.h>
#include <arpa/inet.h>

class Client {
private:
    int PORT;

    int general_socket_descriptor;

    struct sockaddr_in dest_address;
    int address_length;

public:
    Client(std::string address);
    void create_socket();
    void create_connection();
    void request_service(std::string service);
    void send_file(std::string path);
    void receive_file(std::string path);
};


#endif //CLIENT_CLIENT_H
