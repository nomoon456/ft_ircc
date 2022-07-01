#ifndef CHANNEL
#define CHANNEL

#include <iostream>
#include <list>
#include <unistd.h>
#include "Client.hpp"

class Client;

class Channel
{
    private:
        std::string _name;
        std::list<Client *> _clients;
    public:
        Channel(std::string const &name);
        Channel(std::string const &name, Client &client);
        Channel(const Channel &other);
        void    addUser(Client *client);
        Channel &operator=(const Channel &other);
        std::string    getChannelName(void) const;
        virtual ~Channel();
};

#endif