#ifndef CLIENT
#define CLIENT

#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <sstream>
#include <fcntl.h>

class Client {
    private:
        int fd;
        struct sockaddr_in address;
        socklen_t address_size;

        std::string nickname;
        std::string password;
        std::string nickame;
    public:
        Client();
        Client(int fd, struct sockaddr_in address, socklen_t size_address);
        ~Client();
};

#endif