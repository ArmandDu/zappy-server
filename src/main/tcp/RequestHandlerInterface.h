//
// Created by armanddu on 05/07/16.
//

#ifndef ZAPPY_CLIENT_IROUTE_H
#define ZAPPY_CLIENT_IROUTE_H

#include "Request.h"
#include "Response.h"

namespace my_tcp {

    class RequestHandlerInterface {

    public:
        virtual ~RequestHandlerInterface() { };
        virtual void onRequest(Request &request) = 0;
        virtual void onResponse(Response &response) = 0;
        virtual void onConnect(Client &client) = 0;
        virtual void onDisconnect(Client &client) = 0;
    };
}


#endif //ZAPPY_CLIENT_IROUTE_H
