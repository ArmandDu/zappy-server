//
// Created by armanddu on 27/06/16.
//

#ifndef ZAPPY_SERVER_SOCKET_H
#define ZAPPY_SERVER_SOCKET_H

#include <string>
#include <netinet/in.h>

namespace my_tcp {
    class Socket {

    private:

        std::string hostname;
        int port;
        int socketFd;
        bool isOk;

    public:
        Socket(const std::string &hostname, const std::string &port);
        Socket(int fd, sockaddr_in &clientData);
        Socket();

    public:
        void erase();
        bool ok() const;
        bool startListen(int backlog);

        std::string getHostname() const;
        int getPort() const;
        std::string getAddr() const;
        int getFd()const;

    public:
        bool operator<(const Socket &s) const ;
    };

}

#endif //ZAPPY_SERVER_SOCKET_H
