//
// Created by armanddu on 24/07/16.
//

#ifndef ZAPPY_HEADER_H
#define ZAPPY_HEADER_H

#include "Socket.h"
#include "Request.h"

namespace my_tcp {
    class Response : public Request {
    public:
        Response(const Socket &socket, Client &client, const std::string &data);

    };
}

#endif //ZAPPY_HEADER_H
