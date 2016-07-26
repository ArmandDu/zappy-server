//
// Created by armanddu on 28/06/16.
//

#ifndef ZAPPY_CLIENT_DELAY_H
#define ZAPPY_CLIENT_DELAY_H


#include <string>
#include <sstream>
#include <functional>


namespace zappy {

    class Timeout {
    private:

        std::string message;
        struct timeval tv;
        double timeout;
        std::function<void()> callback;


    public:
        Timeout();

    public:
        bool start(double timeout, const std::string &message, const std::function<void()> &cb);
        bool empty() const ;
        bool ready(double deltaTime) const ;
        std::string getMessage() const ;
        void reset();
        double getDuration() const;
        double getTimeout() const;
        const std::function<void()> getCallback() const ;

    public:
        friend std::ostream &operator<<(std::ostream &os, const Timeout &d);

    };
}

#endif //ZAPPY_CLIENT_DELAY_H
