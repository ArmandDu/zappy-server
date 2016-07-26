//
// Created by armanddu on 28/06/16.
//

#include <iostream>
#include <algorithm>
#include <iterator>
#include "AbstractRequestHandler.h"

namespace zappy {


    AbstractRequestHandler::AbstractRequestHandler(Game &game) : game(game){  }


    bool AbstractRequestHandler::isCommand(const std::string &message, const std::string &command) const {
        return 0 == message.compare(0, command.length(), command);
    }

    std::string AbstractRequestHandler::getParams(const std::string &message, const std::string &prefix) {
        auto pos = prefix.length() + 1;
        pos = pos > message.length() ? message.length() : pos;
        return message.substr(pos);
    }

    std::string AbstractRequestHandler::getCommand(const std::string &message) const{
        return message.substr(0, message.find(" "));
    }

}
