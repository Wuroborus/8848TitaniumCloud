#include "Client.h"

Client::Client(std::string address) {
    create_socket();
    PORT = 8848;

    if(inet_pton(AF_INET, address.c_str(), &dest_address.sin_addr)<=0) {
        std::cout << "[ERROR]: Invalid address.\n";
    }
    dest_address.sin_family = AF_INET;
    dest_address.sin_port = htons( PORT );
    address_length = sizeof(dest_address);

    create_connection();
}

void Client::create_socket() {
    if ((general_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("[ERROR]: Socket creation failed.\n");
        exit(EXIT_FAILURE);
    }
    std::cout << "[CLIENT]: Socket created successfully.\n";
}

void Client::create_connection() {
    if (connect(general_socket_descriptor, (struct sockaddr *)&dest_address, sizeof(dest_address)) < 0) {
        perror("[ERROR]: connection failed.\n");
        exit(EXIT_FAILURE);
    }
    std::cout << "[CLIENT]: Connection established successfully.\n";
}

void Client::receive_file(std::string path) {
    FILE* fp;
    if ((fp = fopen(path.c_str(),"ab") ) == nullptr ) {
        std::cout << "[ERROR]: File creation failed.\n";
    }
    std::cout << "[CLIENT]: File created.\n";
    char buffer[1024] = {};
    int valread;
    while(true){
        valread = read(general_socket_descriptor , buffer, 1024);
        std::cout << "[CLIENT]: Received " << valread <<" bytes.\n";
        if(valread == 0)
            break;
        std::cout << "[CLIENT]: Saving data to file.\n";
        fwrite(buffer, 1, valread, fp);
    }
    buffer[valread] = '\0';
    fclose(fp);
    std::cout << "[CLIENT]: File saved.\n";
}

