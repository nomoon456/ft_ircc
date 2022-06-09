#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <sstream>
#include <fcntl.h>
#include "server.hpp"
#include "client.hpp"
#include <unistd.h>
#include <poll.h>

void    client_buffer(Server *server, char *buff_read, int fd)
{
    if (server->clients_buff.find(fd) != server->clients_buff.end())
        server->clients_buff.find(fd)->second.insert(server->clients_buff.find(fd)->second.size(), buff_read);
    else
        server->clients_buff.insert(std::pair<int, std::string>(fd, buff_read));
}

void    *start(Server *server)
{
    struct pollfd pfd;
    pfd.events = POLLIN;
    while (1)
    {
        poll(&pfd, 1, 100);
        for (int i = 0; i < server->getFd() + 1; i++)
        {
            if (pfd.revents == POLLIN) {
                server->server_connexion();
            }
            else
            {
                std::cout << "1" << std::endl;
                int len;
                char buffer[2048];
                std::cout << "Client message " << std::endl;
                memset(buffer, 0, 2048);
                len = read(i, buffer, 2048);
                std::cout << "Client message " << std::endl;
                std::cout << "Client message " << buffer << std::endl;
                if (len <= 0)
                {
                    std::cout << "ADD DECONEXION" << std::endl;
                    break;
                }
                client_buffer(server, buffer, i);
                if (len < 2048 && buffer[len -1] == '\n')
                {
                    std::cout << "ehhe" << std::endl;
                    server->Sender = server->getClient().find(i)->second; //Utilisateur actuel
                    std::cout << "Welcome " << server->Sender << std::endl;
                    server->clients_buff.find(i)->second.clear();
                }
            }
        }
    }
    return NULL;
}

int main(int ac, char **av)
{
    //av[0] = ./irc
    //av[1] = port
    //av[2] = password
    if (ac != 2) {
        std::cout << "Error Args" << std::endl;
        return 1;
    }
    Server server(atoi(av[1]));
    start(&server);
}