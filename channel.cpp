#include "Channel.hpp"

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

void Channel::addUser(Client *user)
{
	std::list<Client*>::iterator end = this->_clients.end();
	for (std::list<Client*>::iterator begin = this->_clients.begin(); begin != end; begin++)
	{
		if (user->getFd() == (*begin)->getFd())
			return ;
	}
	_clients.push_back(user);
}

std::string    Channel::getChannelName(void) const {
    return (this->_name);
}