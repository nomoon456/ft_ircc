#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <sstream>
#include <fcntl.h>

#include "Client.hpp"

Client::Client() {
    
}

Client::Client(int fd, struct sockaddr_in address, socklen_t size_address)
{
    this->_fd = fd;
    this->_address = address;
    this->_address_size = size_address;
    this->_currChannel = "nullptr";
}

int Client::getFd() const {
    return this->_fd;
}

void Client::joinChannel(Channel *channel)
{
    this->channels.push_back(channel);
}