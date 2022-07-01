#ifndef SERVER
#define SERVER

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <locale>
#include <algorithm>
#include <cstring>

#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <sstream>
#include <fcntl.h>
#include "Client.hpp"
#include "Channel.hpp"
#include "Command.hpp"
#include <map>
# include <vector>
# include <iostream>
//# include <stdlib.h>
//# include <sys/socket.h>
//# include <arpa/inet.h>
# include <cstring>
# include <sstream>
#include <poll.h>


class Server {
    private:
        int server_port;
        int server_socket;
        struct sockaddr_in address;
        fd_set reads;
        fd_set cpyReads;
        int maximum;
        int _bind_value;
        int _listen_value;
        struct pollfd _pfd;
        std::map<int, Client*> _users;
        struct timeval      timeout;
        std::list<Channel *> channels;
        std::map<std::string, Command> cmd;
    public:
        Server();
        Server(int server_port);
        ~Server();
        void    exec();
        int     getFd() const;
        int     getSocket() const;
        void    server_setup(int port);
        void server_connexion();
        int     detect_select();
        int     run();
        void    init_cmd();
        std::map<int, Client*> getClient();
        void    joinChannel(Client *client);
        fd_set  getCopyReads();
        fd_set *getCopyReadsAddress();
        void    checkMessage(int fd);
        int     findCommand(std::string data, Client *sender);
        void    sendToServer(std::vector<std::string>::iterator i);
        void    writeOnFd(int fd, std::string str);
        std::vector<std::string> splitData(std::string str);
        std::vector<std::string> splitCommand(std::string message);
        Client *Sender;
        std::map<int, std::string> clients_buff;
};

#endif