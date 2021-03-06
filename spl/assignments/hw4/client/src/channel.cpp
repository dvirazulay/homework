#include "../include/channel.h"
#include "../include/user.h"

#include <string>
#include <algorithm>

Channels Channel::_channels = Channels();

Channel_ptr Channel::getChannel(std::string name) {
    return Channel::getChannel(name, true);
}

Channel_ptr Channel::getChannel(std::string name, bool create) {
    for (Channels::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        Channel_ptr channel = *it;
        if (channel->getName() == name) {
            return channel;
        }
    }

    if (create) {
        Channel_ptr newChannel(new Channel(name));
        _channels.push_back(newChannel);
        return newChannel;
    }

    return Channel_ptr();
}

Channel::Channel(std::string name) : 
    _name(name), 
    _topic(""), 
    _users() 
{
}

void Channel::setTopic(std::string topic) {
    this->_topic = topic;  
}

void Channel::addUser(User_ptr user) {
    this->_users.push_back(user);
}

/**
 * Add a list of users.
**/
void Channel::addUsers(Users users) {
    for (Users::iterator it = users.begin();
         it != users.end();
         ++it)
    {
        this->addUser(*it);
    }
}

void Channel::removeUser(User_ptr user) {
    Users::iterator position = std::find(
                                    this->_users.begin(), 
                                    this->_users.end(),
                                    user
                                );

    if (position != _users.end()) {
        this->_users.erase(position);
    }
}

size_t Channel::getUsersCount() const {
    return this->_users.size();
}

std::string Channel::getName() const {
    return this->_name;
}

std::string Channel::getTopic() const {
    return this->_topic;
}

Users Channel::getUsers() const {
    return this->_users;
}

std::string Channel::toString() const {
    return std::string()
            .append(getName())
            .append(" - ")
            .append(getTopic())
          ;
}
