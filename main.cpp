#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <sstream>
#include <fcntl.h>
#include "Server.hpp"
#include "Client.hpp"
#include <unistd.h>
#include <poll.h>
#include <sys/select.h>

void    client_buffer(Server *server, char *buff_read, int fd)
{
    if (server->clients_buff.find(fd) != server->clients_buff.end())
        server->clients_buff.find(fd)->second.insert(server->clients_buff.find(fd)->second.size(), buff_read);
    else
        server->clients_buff.insert(std::pair<int, std::string>(fd, buff_read));
}

void    *start(Server *server)
{

    int nbFd;

    while (1)
    {
        if ((nbFd = server->detect_select()) == -1)
            break;
        if (nbFd == 0)
            continue;
        for (int i = 0; i < server->getFd() + 1; i++)
        {
            if (FD_ISSET(i, server->getCopyReadsAddress()))
            {
                std::cout << "ON RENTRE " << std::endl;
                if (i == server->getSocket()) {
                    std::cout << "Ok" << std::endl;
                    server->server_connexion();
                }
                else
                {
                    int len;
                    char buffer[2048];
                    memset(buffer, 0, 2048);
                    len = read(i, buffer, 2048);
                    std::cout << "taille: "<< len << "sent: " << buffer << std::endl;
                    if (len <= 0)
                    {
                        std::cout << "ADD DECONEXION" << std::endl;
                        break;
                    }
                    client_buffer(server, buffer, i);
                    if (len < 2048 && buffer[len -1] == '\n')
                    {
                        server->Sender = server->getClient().find(i)->second; //Utilisateur actuel
                        server->checkMessage(i);
                        server->clients_buff.find(i)->second.clear();
                    }
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