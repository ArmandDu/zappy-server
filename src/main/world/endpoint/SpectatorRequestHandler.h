//
// Created by armanddu on 06/07/16.
//

#ifndef ZAPPY_SPECTATORROUTE_H
#define ZAPPY_SPECTATORROUTE_H

#include <memory>
#include "AbstractRequestHandler.h"
#include "../actors/spectator/Spectator.h"
#include "../actors/ActionInterface.h"

namespace zappy {

    class SpectatorRequestHandler : public AbstractRequestHandler {

    private:
        std::vector<std::unique_ptr<ActionInterface<Spectator>>> actions;

    public:
        SpectatorRequestHandler(Game &game);

        void onRequest(my_tcp::Request &request);
        void onResponse(my_tcp::Response &response);
        void onConnect(my_tcp::Client &client);
        void onDisconnect(my_tcp::Client &client);

    private:
        void welcomeClient(my_tcp::Request &request);
        void createSpectator(my_tcp::Request &request);
        void welcomeSpectator(Spectator &spectator, my_tcp::Request &request);

        void route(my_tcp::Request &request, Spectator &spectator);

        bool doAction(Spectator &spectator, std::string command, std::string args);
    };

}


#endif //ZAPPY_SPECTATORROUTE_H
