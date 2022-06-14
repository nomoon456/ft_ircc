#ifndef COMMAND
#define COMMAND

#include <vector>
#include "Client.hpp"

class Server;

void	cmd_list(std::vector<std::string> split, Server *serv, Client *client);
// void    cmd_list(std::vector<std::string> splitted, Server *serv, Client *client);

class Command
{
    private:
        typedef void (*t_commandFunc)(std::vector<std::string> splitted, Server *serv, Client *client);
        t_commandFunc _cmd;
        Command();
    public:
        Command(t_commandFunc cmd);
        ~Command();
        void    exec(std::vector<std::string> split, Server *serv, Client *client);
};

# include "Server.hpp"

#endif