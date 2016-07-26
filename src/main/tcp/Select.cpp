//
// Created by armanddu on 28/06/16.
//

#include <algorithm>
#include "Select.h"
#include "Socket.h"

namespace my_tcp {
    Select::Select() : maxFd(0){
        FD_ZERO(&readFdSet);
        FD_ZERO(&writeFdSet);
        tv = getTimeval(0, Select::USEC_VAL);
    }

    timeval Select::getTimeval(int sec, int usec) const {
        struct timeval t;

        t.tv_sec = sec;
        t.tv_usec = usec;
        return t;
    }

    void Select::addReadFd(int fd) {
        fds.push_back(fd);
        if (fd > maxFd) maxFd = fd;
        FD_SET(fd, &readFdSet);
    }

    void Select::addWriteFd(int fd) {
        fds.push_back(fd);
        if (fd > maxFd) maxFd = fd;
        FD_SET(fd, &writeFdSet);
    }

    int Select::operator()() {
        return select(maxFd + 1, &readFdSet, NULL, NULL, &tv);
    }

    bool Select::hasNewConnexion(my_tcp::Socket &socket) const{
        int fd  = socket.getFd();
        return fd > 0 && FD_ISSET(fd, &readFdSet);
    }

    bool Select::isReadable(int fd) const {
        return fd > 0 && FD_ISSET(fd, &readFdSet);
    }
    bool Select::isWritable(int fd) const {
        return fd > 0 && FD_ISSET(fd, &writeFdSet);
    }


}
