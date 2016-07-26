//
// Created by armanddu on 06/07/16.
//

#ifndef ZAPPY_PLAYERROUTE_H
#define ZAPPY_PLAYERROUTE_H

#include <memory>
#include "AbstractRequestHandler.h"
#include "../actors/ActionInterface.h"
#include "../actors/player/Player.h"

namespace zappy {

    class PlayerRequestHandler : public AbstractRequestHandler{

    private:
       std::vector<std::unique_ptr<ActionInterface<Player>>> actions;

    public:
        PlayerRequestHandler(Game &game);

    public:
        void onRequest(my_tcp::Request &request);
        void onResponse(my_tcp::Response &response);
        void onConnect(my_tcp::Client &client);
        void onDisconnect(my_tcp::Client &client);

    private:
        void route(my_tcp::Request &request, Player &player);

        void welcomeClient(my_tcp::Request &request);
        void createPlayer(my_tcp::Request &request);
        void assignTeam(Player &player, const std::string &name, my_tcp::Request &ServerData);

    };

}

#endif //ZAPPY_PLAYERROUTE_H
