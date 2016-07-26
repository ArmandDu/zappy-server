//
// Created by armanddu on 28/06/16.
//

#include <sys/time.h>
#include <iostream>
#include "Timeout.h"

namespace zappy {
    Timeout::Timeout() : timeout(-1), message(""){

    }

    bool Timeout::start(double timeout, const std::string &message, const std::function<void()> &cb) {
        if (!empty()) return false;
        this->timeout = timeout;
        this->message = message;
        this->callback = cb;
        gettimeofday(&tv, NULL);
        return true;
    }

    bool Timeout::empty() const {
        return message.empty() || timeout == -1;
    }

    bool Timeout::ready(double deltaTime) const {
        double duration = getDuration() * deltaTime;
        return duration >= timeout;
    }

    std::string Timeout::getMessage() const {
        return message;
    }

    const std::function<void()> Timeout::getCallback() const {
        return this->callback;
    }

    void Timeout::reset() {
        message.clear();
        timeout = -1;
    }

    double Timeout::getDuration() const {
        struct timeval ctv;
        gettimeofday(&ctv, NULL);
        return (ctv.tv_sec - tv.tv_sec) + ((ctv.tv_usec - tv.tv_usec) / 1000000.0);
    }

    double Timeout::getTimeout() const {
        return timeout;
    }

    std::ostream &operator<<(std::ostream &os, const Timeout &d) {
        os << "COMMAND: " << d.getMessage() << ": ";
        os << d.getDuration() << "/" << d.getTimeout() << "sec";
        return os;
    }


}

