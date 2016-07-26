//
// Created by armanddu on 04/07/16.
//

#include "Request.h"

namespace my_tcp {
    Request::Request(const Socket &socket, Client &client, const std::string &data): socket(socket),
                                                                                     client(client),
                                                                                     data(data),
                                                                                     toDisconnect(false){

    }

    const Client & Request::getClient() {
        return client;
    }

    const std::string & Request::getData() {
        return data;
    }

    Request &Request::send(const std::string &message) {
        getSession().send(message);
        return *this;
    }

    Request &Request::status(const Client::Status &status) {
        client.setStatus(status);
        return *this;
    }

    void Request::disconnect() {
        client.setToDisconnect(true);
    }

    Client::Session Request::getSession() {
        return client.getSession();
    }

}


