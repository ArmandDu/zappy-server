//
// Created by armanddu on 06/07/16.
//

#include <iostream>
#include <algorithm>
#include "PlayerRequestHandler.h"
#include "../actors/player/actions/TurnAction.h"
#include "../actors/player/actions/MoveAction.h"
#include "../actors/player/actions/ManipulateResourceAction.h"
#include "../actors/player/actions/SeeAction.h"
#include "../actors/player/actions/ConnectNbrAction.h"
#include "../actors/player/actions/BroadcastAction.h"
#include "../actors/player/actions/InventoryAction.h"
#include "../actors/player/actions/ExpelAction.h"
#include "../actors/player/actions/IncantationAction.h"
#include "../actors/player/actions/ForkAction.h"

namespace zappy {

    PlayerRequestHandler::PlayerRequestHandler(Game &game) : AbstractRequestHandler(game) {
        actions.emplace_back(new MoveAction());
        actions.emplace_back(new TurnAction());
        actions.emplace_back(new ManipulateResourceAction());
        actions.emplace_back(new SeeAction());
        actions.emplace_back(new ConnectNbrAction());
        actions.emplace_back(new BroadcastAction());
        actions.emplace_back(new InventoryAction());
        actions.emplace_back(new ExpelAction());
        actions.emplace_back(new IncantationAction());
        actions.emplace_back(new ForkAction());
    }


    void PlayerRequestHandler::onRequest(my_tcp::Request &request) {
        const my_tcp::Client &client = request.getClient();
        if (client.getStatus() == my_tcp::Client::Status::Unset) return ;
        if (!game.isPlayer(client)) return welcomeClient(request);
        else return route(request, game.findPlayer(request.getClient()));
    }

    void PlayerRequestHandler::onResponse(my_tcp::Response &response) {
        if (response.getData() == Player::Message::deadMessage && game.isPlayer(response.getClient()))
            game.disconnect(game.findPlayer(response.getClient()));
    }

    void PlayerRequestHandler::onConnect(my_tcp::Client &client) {
        client.sendMessage(Player::Message::MSG_WELCOME);
    }

    void PlayerRequestHandler::onDisconnect(my_tcp::Client &client) {
        if (game.isPlayer(client))
            game.disconnect(game.findPlayer(client));
    }

    void PlayerRequestHandler::welcomeClient(my_tcp::Request &request) {
        if (game.teamExists(request.getData())) return createPlayer(request);
        return request.disconnect();
    }

    void PlayerRequestHandler::createPlayer(my_tcp::Request &request) {

        Point position;
        Rect size = game.getWorld().getSize();
        position.y = rand() % size.height;
        position.x = rand() % size.width;
        Player::Orientation orientation = static_cast<Player::Orientation >(rand() % Player::Orientation::__COUNT);

        Player player(request.getSession(), size, position, orientation);
        assignTeam(player, request.getData(), request);
    }
    void PlayerRequestHandler::assignTeam(Player &player, const std::string &name, my_tcp::Request &request) {
        if (!game.teamExists(name)) return game.disconnect(player);
        Team &team = game.findTeam(name);
        if (team.getCapacity() <= 0) return game.disconnect(player);
        team.add(player);
        game.addPlayer(player);
        request.status(my_tcp::Client::Status::Connected)
                .send(std::to_string(team.getCapacity()))
                .send(std::to_string(game.getWorld().getSize().width) + " " + std::to_string(game.getWorld().getSize().height));
        std::for_each(game.getSpectators().begin(), game.getSpectators().end(),
                      [&player, this](Spectator &s) {s.pnw(player.getId(), game.getPlayers());});
    }


    void PlayerRequestHandler::route(my_tcp::Request &request, Player &player) {
        std::string command = getCommand(request.getData());
        std::string args = getParams(request.getData(), command);
        auto found = std::find_if(actions.begin(), actions.end(),
                                  [command](std::unique_ptr<ActionInterface<Player>> &action) { return action->isAction(command);}
        );
        if (found != actions.end()) return (*found)->trigger(player, command, args, game);
    }

}