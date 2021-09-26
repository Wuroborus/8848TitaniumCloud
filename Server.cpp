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
    create_socket();
    PORT = 8848;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    address_length = sizeof(address);

    bind_socket();
    set_listen();
    accept_requests();
}

void Server::create_socket() {
    if ((general_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("[ERROR]: Socket creation failed.");
        exit(EXIT_FAILURE);
    }
    std::cout << "[SERVER]: Socket created successfully.\n";
}

void Server::bind_socket() {
    if (bind(general_socket_descriptor, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("[ERROR]: Socket binding failed.");
        exit(EXIT_FAILURE);
    }
    std::cout << "[SERVER]: Socket bound successfully.\n";
}

void Server::set_listen() {
    if (listen(general_socket_descriptor, 3) < 0) {
        perror("[ERROR]: Listening failed.");
        exit(EXIT_FAILURE);
    }
    std::cout << "[SERVER]: Socket is listening.\n";
}

void Server::accept_requests() {
    if ((new_socket_descriptor = accept(general_socket_descriptor, (struct sockaddr *) &address,
                                        (socklen_t *) &address_length)) >= 0) {
        std::cout << "[SERVER]: Connection established.\n";
        char buffer[1024] = {};
        int valread = read(new_socket_descriptor, buffer, 1024);
        buffer[valread] = '\0';
        if (buffer[0] == 'r') {
            send_file(buffer + 8);
        } else if (buffer[0] == 'b') {
            receive_file(buffer + 7);
        } else if (buffer[0] == 'd') {
            dup_dir(buffer + 7);
        }
    } else {
        perror("[ERROR] : Connecting failed.");
        exit(EXIT_FAILURE);
    }
}

void Server::send_file(std::string path) {
    std::fstream file;
    file.open("./backup" + path, std::ios::in | std::ios::binary);
    if (file.is_open()) {
        std::cout << "[SERVER]: File is ready to Transmit.\n";
        std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        std::cout << "[SERVER]: Transmitting " << contents.length() << " Bytes.\n";
        std::cout << "[SERVER]: Sending...\n";

        int bytes_sent = send(new_socket_descriptor, contents.c_str(), contents.length(), 0 );
        std::cout << "[SERVER]: Transmitted " << bytes_sent << " Bytes.\n";

        std::cout << "[SERVER]: File Transfer Complete.\n";
        close(new_socket_descriptor);
        accept_requests();
    } else {
        perror("[ERROR]: File loading failed.");
    }
}

void Server::receive_file(std::string path) {
    std::string::size_type idx = path.rfind('/', path.length());
    std::string par_dir = path.substr(0, idx);
    if (access(("./backup" + par_dir).c_str(), 00) == -1) {
        std::cout << "[SERVER]: Creating directory.\n";
        if (make_dirs(("./backup" + par_dir).c_str()) == -1) {
            std::cout << "[ERROR]: Directory creation failed.\n";
        }
    }
    FILE* fp;
    if ((fp = fopen(("./backup" + path).c_str(),"wb") ) == nullptr ) {
        std::cout << "[ERROR]: File creation failed.\n";
    }
    std::cout << "[SERVER]: File created.\n";
    char buffer[1024] = {};
    int valread;
    while(true){
        valread = read(new_socket_descriptor, buffer, 1024);
//        std::cout << "[SERVER]: Received " << valread <<" bytes.\n";
        if(valread == 0)
            break;
//        std::cout << "[SERVER]: Saving data to file.\n";
        fwrite(buffer, 1, valread, fp);
    }
    buffer[valread] = '\0';
    fclose(fp);
    std::cout << "[SERVER]: File saved.\n";
    close(new_socket_descriptor);
    accept_requests();
}

void Server::dup_dir(std::string path) {
    std::string::size_type idx = path.rfind('/', path.length());
    std::string par_dir = path.substr(0, idx);
    if (access(("./backup" + par_dir).c_str(), 00) == -1) {
        std::cout << "[SERVER]: Creating directory.\n";
        if (make_dirs(("./backup" + par_dir).c_str()) == -1) {
            std::cout << "[ERROR]: Directory creation failed.\n";
        }
    }
    make_dirs(("./backup" + path).c_str());
    std::cout << "[SERVER]: Directory created.\n";
    close(new_socket_descriptor);
    accept_requests();
}
