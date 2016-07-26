//
// Created by armanddu on 12/07/16.
//

#ifndef ZAPPY_IACTION_H
#define ZAPPY_IACTION_H

#include <string>
#include "../../Game.h"

namespace zappy {
    template <class T>
    class ActionInterface {

    public:
        virtual ~ActionInterface() { };

    public:
        virtual bool isAction(const std::string &command) const = 0;
        virtual void trigger(T &actor, const std::string &command, const std::string &args, Game &game) = 0;

    protected:
        bool isCommand(const std::string &message, const std::string &command)const {
            return 0 == message.compare(0, command.length(), command);
        }


    };
}


#endif //ZAPPY_IACTION_H
