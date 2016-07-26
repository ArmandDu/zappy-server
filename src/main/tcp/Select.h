//
// Created by armanddu on 28/06/16.
//

#ifndef ZAPPY_CLIENT_SELECT_H
#define ZAPPY_CLIENT_SELECT_H

#include <sys/select.h>
#include <vector>
#include "Socket.h"

namespace my_tcp {
    class Select {

    private:
        fd_set readFdSet, writeFdSet;
        timeval tv;
        std::vector<int> fds;
        int maxFd;

    private:
        static const int USEC_VAL = 1000;

    private:
        timeval getTimeval(int sec, int usec) const;

    public:
        Select();

    public:
        void addReadFd(int fd);
        void addWriteFd(int fd);
        bool hasNewConnexion(my_tcp::Socket &socket) const;
        bool isReadable(int fd) const;
        bool isWritable(int fd) const;
        int operator()();

    };

}
#endif //ZAPPY_CLIENT_SELECT_H
