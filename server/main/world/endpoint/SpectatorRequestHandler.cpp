// Created by armanddu on 06/07/16.
//

#include <iterator>
#include <algorithm>
#include "SpectatorRequestHandler.h"
#include "../actors/spectator/actions/MapSizeAction.h"
#include "../actors/spectator/actions/TeamListingAction.h"
#include "../actors/spectator/actions/ServerTimeAction.h"
#include "../actors/spectator/actions/MapContentAction.h"
#include "../actors/spectator/actions/PlayerSpawnAction.h"
#include "../actors/spectator/actions/PlayerInventoryAction.h"
#include "../actors/spectator/actions/PlayerPositionOrientationAction.h"
#include "../actors/spectator/actions/PlayerLevelAction.h"

namespace zappy {


    SpectatorRequestHandler::SpectatorRequestHandler(Game &game) : AbstractRequestHandler(game) {
        actions.emplace_back(new MapSizeAction());
        actions.emplace_back(new TeamListingAction());
        actions.emplace_back(new ServerTimeAction());
        actions.emplace_back(new MapContentAction());
        actions.emplace_back(new PlayerSpawnAction());
        actions.emplace_back(new PlayerInventoryAction());
        actions.emplace_back(new PlayerPositionOrientationAction());
        actions.emplace_back(new PlayerLevelAction());
    }


    void zappy::SpectatorRequestHandler::onRequest(my_tcp::Request &request) {
        const my_tcp::Client &client = request.getClient();
        if (client.getStatus() == my_tcp::Client::Status::Unset) return ;
        if (!game.isSpectator(client)) return welcomeClient(request);
        else return route(request, game.findSpectator(request.getClient()));
    }
    void SpectatorRequestHandler::onResponse(my_tcp::Response &response) { }

    void SpectatorRequestHandler::onConnect(my_tcp::Client &client) {
        return client.sendMessage(Spectator::Message::MSG_WELCOME);
    }

    void SpectatorRequestHandler::onDisconnect(my_tcp::Client &client) {
        if (game.isSpectator(client)) game.disconnect(game.findSpectator(client));
    }



    void SpectatorRequestHandler::welcomeClient(my_tcp::Request &request) {
        if (isCommand(request.getData(), Spectator::Message::Name)) return createSpectator(request);
        return request.disconnect();
    }

    void SpectatorRequestHandler::createSpectator(my_tcp::Request &request) {
        Spectator spectator(request.getSession());
        game.addSpectator(spectator);
        welcomeSpectator(spectator, request);
    }

    void SpectatorRequestHandler::welcomeSpectator(Spectator &spectator, my_tcp::Request &request) {
        std::string message = request.getData();
        if (message != Spectator::Message::Name) return spectator.disconnect();
        doAction(spectator, Spectator::Message::MapSize, "");
        doAction(spectator, Spectator::Message::Sgt, "");
        doAction(spectator, Spectator::Message::Mct, "");
        doAction(spectator, Spectator::Message::Tna, "");
        for (auto &player: game.getPlayers()) {
            doAction(spectator, Spectator::Message::Pnw, player.getId());
        }
        request.status(my_tcp::Client::Status::Connected);
    }

    bool SpectatorRequestHandler::doAction(Spectator &spectator, std::string command, std::string args) {
        auto found = std::find_if(actions.begin(), actions.end(),
                                  [command](std::unique_ptr<ActionInterface<Spectator>> &action) { return action->isAction(command);}
        );
        if (found != actions.end()) (*found)->trigger(spectator, command, args, game);
        return found != actions.end();
    }

    void SpectatorRequestHandler::route(my_tcp::Request &request, Spectator &spectator) {
        std::string command = getCommand(request.getData());
        std::string args = getParams(request.getData(), command);
        if  (!doAction(spectator, command, args))
            return (void) request.send(Spectator::Message::MessageUnknown);
    }
}
