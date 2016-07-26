//
// Created by armanddu on 27/06/16.
//

#include <netinet/in.h>
#include <iostream>
#include <algorithm>
#include <cstring>
#include "Client.h"

namespace my_tcp {


    int Client::count = 0;

    Client::Client() : id(count++),
                       status(Unset),
                       toDisconnect_(false),
                       socket_() { }

    Client::Client(int fd, sockaddr_in clientData): Client() {
        connect(fd, clientData);
    }

    bool Client::connect(int fd, sockaddr_in clientData) {
        socket_ = Socket(fd, clientData);
        this->status = Connected;
        return fd > 0;
    }

    int Client::getSocketFd() const {
        return socket_.getFd();
    }

    std::string Client::getIp() const {
        return socket_.getHostname();
    }
    int Client::getPort() const {
        return socket_.getPort();
    }


    std::string Client::getMessage() {
        if (status == Unset) throw std::string("Error: Client Not Connected!");
        char buff[BUFF_SIZE];
        memset(buff, 0, sizeof(buff));
        if (-1 == (recv(getSocketFd(), buff, sizeof(buff), MSG_NOSIGNAL)) || buff[0] <= 4) return setToDisconnect(true), "";
        partialContent += std::string(buff);
        unsigned long pos;
        if((pos = partialContent.find('\n')) == partialContent.npos) return "";
        std::string message = partialContent.substr(0, pos);
        partialContent.erase(0, pos);
        purifyMessage(partialContent);
        purifyMessage(message);
        std::cout << " >> RECEIVED FROM " << *this << ": \"" << message  << "\""<< std::endl;
        return message;
    }

    void Client::sendMessage(const std::string &message) {
        if (status == Unset) throw std::string("Error: Client Not Connected!");
        std::string buf = std::string(message.c_str()) + "\n";
        if ( status ==  Disconnected || -1 == send(getSocketFd(), buf.c_str(), buf.size(), MSG_NOSIGNAL)) {
            disconnect();
            return ;
        }
        std::cout << " << SENT TO " << *this << ": \"" << message  << "\""<< std::endl;
    }

    void Client::purifyMessage(std::string &message) const {
        message.erase(std::remove(message.begin(), message.end(), '\n'), message.end());
        message.erase(std::remove(message.begin(), message.end(), '\r'), message.end());
    }

    void Client::setStatus(Status s) {
        if (s > Disconnected) this->status = s;
    }

    Client::Status Client::getStatus() const {
        return status;
    }

    bool Client::isDisconnected() const {
        return status == Disconnected;
    }

    std::string Client::getId() const {
        return std::to_string(id);
    }

    std::list<std::string> Client::getOutBuffer() {
        return outBuffer;
    }

    const std::list<std::string> &Client::getOutBuffer() const {
        return outBuffer;
    }


    unsigned long Client::pushOutBuffer(const std::string message) {
        outBuffer.push_back(message);
        return outBuffer.size();
    }

    bool Client::popOutBuffer(std::string &res) {
        if (outBuffer.empty()) {
            return false;
        }
        res = outBuffer.front();
        outBuffer.pop_front();
        return true;
    }


    bool Client::operator<(const Client &b) const {
        return getSocketFd() < b.getSocketFd();
    }

    bool Client::operator==(const Client &b) const {
        return getSocketFd() == b.getSocketFd();
    }
    std::ostream &operator<<(std::ostream &os, const Client &c) {
        os << "[FD:" << c.getSocketFd() << " IP:" << c.getIp()
        << " PORT:" << c.getPort()
        << " ID:" << c.getId() << "]";
        return os;

    }

    bool Client::canDisconnect() const {
        return status != Disconnected;
    }

    bool Client::toDisconnect() const {
        return toDisconnect_;
    }

    void Client::setToDisconnect(bool t) {
        toDisconnect_ = t;
    }

    void Client::disconnect() {
        if (canDisconnect() && toDisconnect()) {
            status = Disconnected;
            outBuffer.clear();
            socket_.erase();
            std::cout << "CLIENT " << *this << " HAS DISCONNECTED" << std::endl;
        } else if (status == Client::Status::Disconnected)
            std::cerr << "CLIENT " << *this << " ALREADY DISCONNECTED" << std::endl;
    }

    Client::Session Client::getSession() {
        return Session(*this);
    }

    void Client::Session::send(const std::string &message) {
        client_.pushOutBuffer(message);
    }

    Client::Session::Session(Client &client)  : client_(client) { }

}



