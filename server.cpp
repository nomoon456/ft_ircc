/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomoon <nomoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:32:07 by jiglesia          #+#    #+#             */
/*   Updated: 2022/06/10 16:16:55 by nomoon           ###   ########.fr       */
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
#include "server.hpp"
#include "client.hpp"

Server::Server() {};

Server::Server(int port)
{
    this->server_port = port;
    server_setup(this->server_port);
}

Server::~Server()
{
    
}

void    Server::server_setup(int port)
{
    struct sockaddr_in address;
    int h = -1;
    this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    bind(this->server_socket, (struct sockaddr*)&address, sizeof(address));
    listen(this->server_socket, 5);
    this->maximum = this->server_socket;
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
        this->clients_all.insert(std::pair<int, Client*>(socket, new_client));
        FD_SET(socket, &(this->reads));
        std::cout << "Client Connected\n" << std::endl;
        if (this->maximum < socket)
            this->maximum = socket;
    }
    else
        std::cout << "Client Socket Not Accepted" << std::endl;
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
    return this->clients_all;
}

fd_set  Server::getCopyReads() {
    return this->cpyReads;
}

fd_set *Server::getCopyReadsAddress() {
    return (&(this->cpyReads));
}