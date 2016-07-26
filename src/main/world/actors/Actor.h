//
// Created by armanddu on 07/07/16.
//

#ifndef ZAPPY_IACTOR_H
#define ZAPPY_IACTOR_H

#include "../../tcp/Client.h"

namespace zappy {
    class Actor {

    public:
        class Message {
        public:
            static const std::string Ko;
            static const std::string OK;
            static const std::string MSG_WELCOME;

        private:
            Message() {};
        };

    protected:
        my_tcp::Client::Session session;
        bool exited;

    protected:
        Actor(my_tcp::Client::Session session);

    public:
        my_tcp::Client::Session & getSession();
        std::string getId() const;
        const bool hasExited() const { return exited;}
        virtual void disconnect() = 0;

    public:
        bool operator==(const Actor &a);

    };
}


#endif //ZAPPY_IACTOR_H
