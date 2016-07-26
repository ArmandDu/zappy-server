//
// Created by armanddu on 27/06/16.
//

#ifndef ZAPPY_SERVER_SERVER_H
#define ZAPPY_SERVER_SERVER_H

#include <string>
#include <vector>
#include <map>
#include "Socket.h"
#include "Select.h"
#include "RequestHandlerInterface.h"

namespace my_tcp {

    class Server {

    private:
        static const int MAX_BACKLOG = 50;
    private:
        bool run;
        std::string status;
        std::vector<Socket> sockets;
        std::list<Client> clients;
        RequestHandlerInterface &requestHandler;

    public:
        Server(RequestHandlerInterface &requestsHandler);
        ~Server();

    public:
        bool listen(const std::string &port, const std::string &addr);
        bool listen(const std::string &port);
        const std::string &getStatus() const;
        bool isRunning() const;

        void update();
        bool start();

    private:
        std::string error(const std::string &message) const;
        void handle(Socket &socket);
        void processSelect(const Select &select, Socket &socket);
        void initSelect(Select &s, Socket &socket);
        void acceptNewClient(Socket &socket);
        bool acceptNewClient(Socket &socket, Client &client);
        void removeDisconnectedClients(Socket &socket);
        void sendResponse(Client &client, Socket &socket);
        void sendRequest(Client &client, Socket &socket);


    };
}

#endif //ZAPPY_SERVER_SERVER_H
