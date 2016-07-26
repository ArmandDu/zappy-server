//
// Created by armanddu on 27/06/16.
//

#include <iostream>
#include <algorithm>
#include <cstring>

#include "Server.h"
#include "Response.h"

namespace my_tcp {

    Server::Server(RequestHandlerInterface &requestsHandler) : run(false), requestHandler(requestsHandler) {  }

    Server::~Server() {
        for (Socket &socket: sockets) {
            socket.erase();
        }
    }

    bool Server::listen(const std::string &port, const std::string &addr) {
        Socket socket(addr, port);

        if (!socket.ok() || !(socket.startListen(Server::MAX_BACKLOG))) {
            status = error("Failed to create socket at: " + port);
            return false;
        }
        sockets.push_back(socket);
        return status.empty();
    }


    bool Server::listen(const std::string &port) {
        return listen(port, "127.0.0.1");
    }

    bool Server::start() {
        run = status.empty();
        return run;
    }

    void Server::update() {
        if (!isRunning()) throw std::string("Server not started");
        for (auto &socket: sockets) handle(socket);
    }

    const std::string &Server::getStatus() const {
        return status;
    }

    bool Server::isRunning() const {
        return run;
    }

    std::string Server::error(const std::string &message) const { return message + ": " +  std::string(strerror(errno)); }

    void Server::handle(Socket &socket) {
        Select select;
        removeDisconnectedClients(socket);
        initSelect(select, socket);
        int nfds = select();
        if (nfds == -1) {
            std::cerr << "WARNING: " << error("select failed") << std::endl;
            return ;
        }
        processSelect(select, socket);
    }

    void Server::initSelect(Select &s, Socket &socket) {
        s.addReadFd(socket.getFd());
        auto socketsClients = clients;
        for (auto &client: socketsClients) {
            s.addReadFd(client.getSocketFd());
            if (!client.getOutBuffer().empty()) s.addWriteFd(client.getSocketFd());
        }
    }

    void Server::processSelect(const Select &select, Socket &socket) {

        if (select.hasNewConnexion(socket)) acceptNewClient(socket);
        else {
            for (auto &client: clients) {
                if (select.isReadable(client.getSocketFd())) sendRequest(client, socket);
                if (select.isWritable(client.getSocketFd())) sendResponse(client, socket);
            }
        }
    }

    void Server::acceptNewClient(Socket &socket) {
        Client client;
        if (!acceptNewClient(socket, client)) {
            status = error("Failed to accept new client");
            return;
        }
        std::cout << "NEW CLIENT CONNECTED: " << client << std::endl;
        requestHandler.onConnect(client);
        clients.push_back(client);
    }

    bool Server::acceptNewClient(Socket &socket, Client &client) {
        struct sockaddr_in newClientData;

        int len = sizeof(newClientData);
        int fd;
        if (-1 == (fd = accept(socket.getFd(), (sockaddr *) &newClientData, (socklen_t *) &len))) {
            return false;
        }
        return client.connect(fd, newClientData);
    }


    void Server::sendRequest(Client &client, Socket &socket) {
        std::string message = client.getMessage();
        Request request(socket, client, message);
        requestHandler.onRequest(request);
    }

    void Server::sendResponse(Client &client, Socket &socket) {
        std::string message;
        client.popOutBuffer(message);
        Response response(socket, client, message);
        client.sendMessage(message);
        requestHandler.onResponse(response);
    }

    void Server::removeDisconnectedClients(Socket &socket) {
        clients.remove_if([&socket, this](Client &client){
            if (client.toDisconnect() && client.canDisconnect()) {
                requestHandler.onDisconnect(client);
                client.disconnect();
            }
            return client.isDisconnected();
        });
    }

}
