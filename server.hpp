#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <sstream>
#include <fcntl.h>
#include <map>
#include "client.hpp"

class Server {
    private:
        int server_port;
        int server_socket;
        struct sockaddr_in address;
        fd_set reads;
        int maximum;
        std::map<int, Client*> clients_all;
    public:
        Server();
        Server(int server_port);
        ~Server();
        int     getFd() const;
        int     getSocket() const;
        void    server_setup(int port);
        void server_connexion();
        std::map<int, Client*> getClient();
        Client *Sender;
        std::map<int, std::string> clients_buff;
};

