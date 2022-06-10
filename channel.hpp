#ifndef CHANNEL
#define CHANNEL

#include <iostream>
#include <list>
#include <unistd.h>

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
        Channel &operator=(const Channel &other);
        virtual ~Channel();
};

#endif