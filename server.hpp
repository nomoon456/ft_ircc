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
#include "channel.hpp"

class Server {
    private:
        int server_port;
        int server_socket;
        struct sockaddr_in address;
        fd_set reads;
        fd_set cpyReads;
        int maximum;
        std::map<int, Client*> clients_all;
        struct timeval      timeout;
            std::list<Channel *> channels;
            // std::map<std::string, Command> cmd;
    public:
        Server();
        Server(int server_port);
        ~Server();
        int     getFd() const;
        int     getSocket() const;
        void    server_setup(int port);
        void server_connexion();
        int     detect_select();
        std::map<int, Client*> getClient();
        fd_set  getCopyReads();
        fd_set *getCopyReadsAddress();
        Client *Sender;
        std::map<int, std::string> clients_buff;
};

