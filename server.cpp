/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomoon <nomoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:32:07 by jiglesia          #+#    #+#             */
/*   Updated: 2022/06/30 15:29:48 by nomoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <sstream>
#include <fcntl.h>
#include "Client.hpp"
#include <utility>
#include <cstdio>
#include <unistd.h>
#include "Server.hpp"
#include "Command.hpp"

Server::Server() {};

Server::Server(int port)
{
    this->server_port = port;
    server_setup(this->server_port);
}

Server::~Server()
{
    
}

// void Server::server_setup(int port) { 
//     server_port = port;
//     this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
// 	_pfd.fd = server_socket;
// 	_pfd.events = POLLIN;
// 	memset(&address, 0, sizeof(address));
// 	address.sin_family = AF_INET;
//     address.sin_port = htons(port);
// 	_bind_value = bind(server_socket, (struct sockaddr *)&address, sizeof(address));
// 	if (_bind_value < 0){
// 		std::cout << "could not bind\n";
// 		throw std::exception();
// 	}
// 	_listen_value = listen(server_socket, 1);
// 	if (_listen_value < 0)
// 		throw std::exception();
// }

void    Server::server_setup(int port)
{
    struct sockaddr_in address;
    int h = -1;

    this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    _pfd.fd = server_socket;
    _pfd.events = POLLIN;
    std::cout << server_socket << std::endl;
    setsockopt(this->server_socket, SOL_SOCKET, SO_REUSEADDR, &h, sizeof(int));
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    bind(this->server_socket, (struct sockaddr*)&address, sizeof(address));
    listen(this->server_socket, 5);
    FD_ZERO(&(this->reads));
	FD_SET(this->server_socket, &(this->reads));
    this->maximum = this->server_socket;
    init_cmd();
}

// void     Server::connexion()
// {
//     int client_socket;
//     struct sockaddr_in clnt_adr;
// 	socklen_t adr_sz = sizeof(clnt_adr);

//     client_socket = accept(this->serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
    
//     if (client_socket != -1)
// 	{			
// 		fcntl(client_socket, F_SETFL, O_NONBLOCK);
// 		Client *new_client = new Client(client_socket, clnt_adr, adr_sz);
// 		new_client->setIsServer(false); 									// IMPORTANT à gerer:  valeur par defaul de client 
// 		this->clients.insert(std::pair<int, Client*>(client_socket, new_client));
// 		FD_SET(client_socket, &(this->reads));
// 		std::cout << "[Client connected]" << std::endl;
// 		new_client->setConnectionStatus(true);
// 		if (this->fd_max < client_socket)
// 			this->fd_max = client_socket;
// 	}
// }

void    Server::joinChannel(Client *client) {
    std::cout << "letwgoo" << std::endl;
    Channel *new_chan = new Channel("Default");
    channels.push_back(new_chan);
    new_chan->addUser(client);
	client->joinChannel(new_chan);
}

void    Server::server_connexion()
{
    int socket;
    struct sockaddr_in client_address;
    socklen_t remote_address = sizeof(client_address);
    socket = accept(this->server_socket, (struct sockaddr*)&client_address, &remote_address);
    if (socket != -1) {
        fcntl(socket, F_SETFL, O_NONBLOCK);
        Client *new_client = new Client(socket, client_address, remote_address);
        this->_users.insert(std::pair<int, Client*>(socket, new_client));
        std::cout << "Accepted new client @ "  << std::endl;
        FD_SET(socket, &(this->reads));
        std::cout << "Client Connected\n" << std::endl;
        if (this->maximum < socket)
            this->maximum = socket;
        joinChannel(new_client);
    }
    else
        std::cout << "Client Socket Not Accepted" << std::endl;
}

void    Server::checkMessage(int fd)
{
    std::cout << "CHECK MESSAGE " << std::endl;
    std::vector<std::string> dataSplitted = splitData(this->clients_buff[fd]);
    std::vector<std::string>::iterator dataEnd = dataSplitted.end();
    for (std::vector<std::string>::iterator i = dataSplitted.begin(); i != dataEnd; i++)
    {
        if (findCommand((*i), Sender))
            return ;
        else
        {
            // sendToServer(i);
        }
    }
}

int     Server::findCommand(std::string str, Client *sender)
{
    std::cout << "sup g" << std::endl;
    std::cout << str << std::endl;
    std::vector<std::string> cmd_split = splitCommand(str);
    if (!cmd_split.empty() && !cmd_split[0].empty() && this->cmd.find(cmd_split[0]) != this->cmd.end())
    {
        this->cmd.find(cmd_split[0])->second.exec(cmd_split, this, sender);
        std::cout << "Commad exec" << std::endl;
    }
    else
    {
        return (0);
    }
    return (1);
}

std::vector<std::string> Server::splitData(std::string str)
{
    std::vector<std::string>    splitted;
    size_t                      i = 0;
    std::string                 temp;
    if (str.empty())
        return std::vector<std::string>();
    while ((i = str.find_first_of("\n")) != std::string::npos)
    {
        temp = str.substr(0, i);
        if (!temp.empty())
            splitted.push_back(temp);
        str.erase(0, i + 1);
    }
    if (!str.empty())
        splitted.push_back(str);
    return (splitted);
    
}

std::vector<std::string> Server::splitCommand(std::string message)
{
    std::vector<std::string> splitted;
    size_t i = 0;
    std::string temp;
    std::string whsp("\f\v\t\n\r"); //the whsp parameter is a string containing all the char which are white space
    if (message[0] == ' ')
        return std::vector<std::string>();
    if (message.length() == 0)
        return std::vector<std::string>();
    if ((i = message.find_last_not_of(whsp)) != std::string::npos) //find_last_not_of = npos = find non matching character in a string from the end
        message.erase(i + 1);
    else
        return (splitted);
    if ((i = message.find_first_not_of(whsp)) != std::string::npos) //npos = max value of size_t
        message = message.substr(i);
    else
        return (splitted);
    while ((i = message.find_first_of(whsp)) != std::string::npos)
    {
        temp = message.substr(0, i);
        if (!temp.empty()) {
            splitted.push_back(temp);
        }
        message.erase(0, i + 1);
        if (!message.empty() && message[0] == ':')
            break;
    }
    if (!message.empty())
        splitted.push_back(message);
    if (splitted.size() > 1 && splitted.back().size() > 0 && splitted.back()[0] == ':')
        splitted.back() = splitted.back().substr(1);
    return (splitted);
}

void    Server::sendToServer(std::vector<std::string>::iterator i)
{
    std::map<int, Client*>::iterator iEnd = this->_users.end();
    std::cout << "8" << std::endl;
    for (std::map<int, Client *>::iterator iBeg = this->_users.begin(); iBeg != iEnd; ++i)
    {
        // std::cout << "777" << std::endl;
        writeOnFd((*iBeg).second->getFd(), (*i + "\n").c_str());
        // std::cout << "9999" << std::endl;
    }
}

void    Server::init_cmd()
{
    std::cout << "hhhh" << std::endl;
    this->cmd.insert(std::pair<std::string, Command>("/list", cmd_list));
    this->cmd.insert(std::pair<std::string, Command>("LIST", cmd_list));
}

int Server::detect_select() {
    int ret;

    this->cpyReads = this->reads;
    this->timeout.tv_sec = 1;
    this->timeout.tv_usec = 1000;
    ret = select(this->maximum + 1, &(this->cpyReads), 0, 0, &(this->timeout));
    return (ret);
}

int Server::getFd() const {
    return this->maximum;
}

int Server::getSocket() const {
    return this->server_socket;
}

std::map<int, Client*> Server::getClient() {
    return this->_users;
}

fd_set  Server::getCopyReads() {
    return this->cpyReads;
}

fd_set *Server::getCopyReadsAddress() {
    return (&(this->cpyReads));
}

void    Server::writeOnFd(int fd, std::string str)
{
    write(fd, str.c_str(), str.size());
}

