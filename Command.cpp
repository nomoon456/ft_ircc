#include "Command.hpp"

Command::Command(t_commandFunc cmd) : _cmd(cmd) {}

Command::~Command() {}

void    Command::exec(std::vector<std::string> splitted, Server *server, Client *client)
{
    this->_cmd(splitted, server, client);
}

void    cmd_list(std::vector<std::string> split, Server *serv, Client *client) {
    // if (split.size() >= 1)
    // {
    //     if (split.size() == 1)
    //     {
            std::cout << "EHEHHEHEHE" << std::endl;
            //std::list<Channel *> temp = serv->getChannels(); AJOUTER FONCTION GET CHANNEL
            // std::list<Channel *>::iterator channelList = temp.begin();
            // for (std::list<Channel *>::iterator end = tmp.end(); channelList != end; channelList++)
                // serv->writeOnFd(client->getFd(), (*channelList)->getChannelName() + "\n"); AJOUTER GET CHANNELNAME
    //     }
    // }
}