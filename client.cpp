#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <sstream>
#include <fcntl.h>

#include "client.hpp"

Client::Client() {
    
}

Client::Client(int fd, struct sockaddr_in address, socklen_t size_address)
{

}