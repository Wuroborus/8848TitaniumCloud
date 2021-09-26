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

void Client::request_service(std::string service) {
    send(general_socket_descriptor, service.c_str(), service.length(), 0);
    std::cout << "Requested server to " << service << ".\n";
}

void Client::send_file(std::string path) {
    std::fstream file;
    file.open(path, std::ios::in | std::ios::binary);
    if (file.is_open()) {
        std::cout << "[CLIENT]: File is ready to Transmit.\n";
        std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        std::cout << "[CLIENT]: Transmitting " << contents.length() << " Bytes.\n";
        std::cout << "[CLIENT]: Sending...\n";

        int bytes_sent = send(general_socket_descriptor, contents.c_str(), contents.length(), 0 );
        std::cout << "[CLIENT]: Transmitted " << bytes_sent << " Bytes.\n";

        std::cout << "[CLIENT]: File Transfer Complete.\n";
    } else {
        perror("[ERROR]: File loading failed.");
    }
}

void Client::receive_file(std::string path) {
    FILE* fp;
    if ((fp = fopen(path.c_str(),"wb") ) == nullptr ) {
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
