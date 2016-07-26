//
// Created by armanddu on 28/06/16.
//

#ifndef ZAPPY_CLIENT_ROUTE_H
#define ZAPPY_CLIENT_ROUTE_H

#include <string>
#include <map>
#include "../../tcp/Client.h"
#include "../../tcp/Request.h"
#include "../../tcp/RequestHandlerInterface.h"
#include "../Resource.h"
#include "../../Game.h"

namespace zappy {

    class AbstractRequestHandler : public my_tcp::RequestHandlerInterface {
        //TODO remove every need to use namespace my_tcp:: below this class (encapsulate Request and co)

    protected:
        Game &game;

    public:
        AbstractRequestHandler(Game &game);

    protected:
        bool isCommand(const std::string &message, const std::string &command) const;
        std::string getParams(const std::string &message, const std::string &prefix);
        std::string getCommand(const std::string &message) const;
    };
}

#endif //ZAPPY_CLIENT_ROUTE_H
