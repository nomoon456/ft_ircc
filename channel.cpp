#include "channel.hpp"

Channel::Channel(std::string const &name) : _name(name) {};

Channel::Channel(const Channel &other) {*this = other;}

Channel &Channel::operator=(const Channel &other)
{
    _name = other._name;
    return *this;
}

Channel::Channel(std::string const &name, Client &client) {
    _name = name;
    _clients.push_back(&client);
}

Channel::~Channel() {}