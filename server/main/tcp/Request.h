//
// Created by armanddu on 04/07/16.
//

#ifndef ZAPPY_CLIENT_REQUEST_H
#define ZAPPY_CLIENT_REQUEST_H


#include "Client.h"
#include "Socket.h"

namespace my_tcp {
    class Request {

    private:
        const Socket socket;
        Client &client;
        const std::string data;
        bool toDisconnect;

    public:
        Request(const Socket &socket, Client &client, const std::string &data);

        const Client & getClient();
        const std::string & getData();

        Request & send(const std::string &message);
        Request & status(const Client::Status &status);
        void disconnect();


        Client::Session getSession();

    };
}

#endif //ZAPPY_CLIENT_REQUEST_H
