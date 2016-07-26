//
// Created by armanddu on 27/06/16.
//

#include <sys/socket.h>
#include <iostream>
#include "Socket.h"
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

namespace my_tcp {

    Socket::Socket() : isOk(false) {}

    Socket::Socket(int fd, sockaddr_in &clientData) : Socket() {
        socketFd = fd;
        hostname= inet_ntoa(clientData.sin_addr);
        port = ntohs(clientData.sin_port);
        isOk = socketFd > STDERR_FILENO && !hostname.empty() && port > 0;
    }

    Socket::Socket(const std::string &hostname, const std::string &port) : Socket() {
        struct addrinfo *res, *it;

        struct addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;

        if (-1 == (getaddrinfo(hostname.c_str(), port.c_str(), &hints, &res))) return ;
        int enable = 1;
        for (it = res; it != NULL; it = it->ai_next) {
            if (-1 != (this->socketFd = socket(AF_INET, SOCK_STREAM, 0)) &&
                -1 != (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)))) {
                if (-1 != (bind(socketFd, it->ai_addr, it->ai_addrlen))) {
                    this->hostname = hostname;
                    this->port = atoi(port.c_str());
                    freeaddrinfo(res);
                    isOk = socketFd > STDERR_FILENO && !hostname.empty() && !port.empty();
                    return ;
                } else
                    close(socketFd);
                socketFd = -1;
            }
        }
    }

    bool Socket::ok() const{
        return isOk;
    }

    bool Socket::startListen(int backlog) {
        return -1 != (listen(socketFd, backlog));
    }

    std::string Socket::getHostname() const {
        return hostname;
    }

    int Socket::getPort() const {
        return port;
    }

    std::string Socket::getAddr() const {
        return getHostname()+ ":" + std::to_string(getPort());
    }

    int Socket::getFd()const {
        return socketFd;
    }

    bool Socket::operator<(const Socket &s) const {
        return getFd() < s.getFd();
    }

    void Socket::erase() {
        if (isOk) close(socketFd);
    }


}

