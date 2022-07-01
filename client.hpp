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
#include <list>
// #include "Channel.hpp"

class Channel;

class Client {
    private:
        int _fd;
        struct sockaddr_in _address;
        socklen_t _address_size;
        std::string _nickname;
        std::string _password;
        std::string _nickame;
        std::string _currChannel;
        std::list<Channel*> channels;
    public:
        Client();
        Client(int fd, struct sockaddr_in address, socklen_t size_address);
        ~Client();
        int getFd() const;
        void    joinChannel(Channel *channel);
};

#endif