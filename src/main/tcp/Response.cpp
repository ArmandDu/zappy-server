//
// Created by armanddu on 24/07/16.
//

#include "Response.h"
namespace my_tcp {
    Response::Response(const Socket &socket, Client &client, const std::string &data) : Request(socket, client, data) {}
}
