#include "../include/message.h"
#include "../include/user.h"

#include <sstream>
#include <ostream>
#include <istream>
#include <iomanip>

Message::Message(std::string text) :
    _user(NULL),
    _text(text),
    _nick(""),
    _timestamp(time(0)),
    _type(Message::DEFAULT)
{
}

Message::Message(std::string text, User* user) :
    _user(user),
    _text(text),
    _nick(user->getFullNick()),
    _timestamp(time(0)),
    _type(Message::DEFAULT)
{
}

Message::Message(std::string text, Message::Type type) :
    _user(NULL),
    _text(text),
    _nick(""),
    _timestamp(time(0)),
    _type(type)
{
}

Message::Message(std::string text, User* user, Message::Type type) :
    _user(user),
    _text(text),
    _nick(user->getFullNick()),
    _timestamp(time(0)),
    _type(type)
{
}

Message::Message (Message& other) :
    _user(new User(*other.getUser())),
    _text(other.getText()),
    _nick(other.getNick()),
    _timestamp(other.getTimestamp()),
    _type(Message::DEFAULT)
{
}

Message Message::operator=(const Message& other) {
    if (this == &other) {
        return *this;
    }

    this->_user = new User(*other.getUser());
    this->_text = other.getText();
    this->_nick = other.getNick();
    this->_type = other.getType();
    return *this;
}

User* Message::getUser() const {
    return _user;
}

std::string Message::getText() const {
    return _text;
}

std::string Message::getNick() const {
    return _nick;
}

short Message::getType() const {
    return _type;
}

time_t Message::getTimestamp() const {
    return _timestamp;
}

std::string Message::getTimestampString() const {
    struct tm* now = localtime(&_timestamp);
    std::ostringstream time;
    time << std::setfill('0') << std::setw(2) << (1 + now->tm_hour) 
         << ":" 
         << std::setfill('0') << std::setw(2) << now->tm_min;
    return time.str();
}

std::string Message::toString() const {
    std::string str;
     
    str.append(getTimestampString()).append(" ");

    if (Message::PRIVATE == this->getType()) {
        str.append("<= ").append(this->getNick()).append(": ");
    } else if (Message::SYSTEM == this->getType()) {
        str.append("*** ");
    } else if (Message::DEBUG == this->getType()) {
        str.append("==debug==  ");
    } else if (Message::ACTION == this->getType()) {
        str.append("* ").append(this->getNick()).append(" ");
    } else {
        str.append("<").append(this->getNick()).append("> ");
    }

    str.append(this->getText());

    return str;
}
