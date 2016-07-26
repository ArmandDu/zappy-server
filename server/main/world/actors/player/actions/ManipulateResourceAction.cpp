//
// Created by armanddu on 12/07/16.
//

#include <algorithm>
#include <iostream>
#include "ManipulateResourceAction.h"

namespace  zappy {

    bool ManipulateResourceAction::isAction(const std::string &command) const {
        return isCommand(command, Player::Command::Take) ||
               isCommand(command, Player::Command::Put);
    }

    void ManipulateResourceAction::trigger(Player &actor, const std::string &command,
                                           const std::string &args, Game &game) {
        if (isCommand(command, Player::Command::Take)) return take(actor, args, game);
        if (isCommand(command, Player::Command::Put)) return put(actor, args, game);
    }

    void ManipulateResourceAction::take(Player &player, const std::string &item, Game &game) {
        auto cb = [&player, item, &game, this]() {
            auto &square = game.getWorld().getSquare(player.getPosition().x, player.getPosition().y);
            std::function<bool(const Resource &)> pred = [&item, &square](const Resource &resource) {
                return resource.getName() == item && square.getQuantity(resource) > 0;
            };
            int newStock = 1;
            if (item.empty()) return player.getSession().send(Actor::Message::Ko);
            auto found = std::find_if(World::Resources::resources.begin(), World::Resources::resources.end(), pred);
            if (found != World::Resources::resources.end()) {
                auto resource = *found;
                player.getInventory().addStock(resource, newStock);
                square.addResource(resource, -newStock);
                player.getSession().send(Actor::Message::OK);
                std::for_each(game.getSpectators().begin(), game.getSpectators().end(),
                              [&player, &game, resource](Spectator &s) {
                                  s.pgt(player.getId(), game.getPlayers(), resource);
                                  s.pin(player.getId(), game.getPlayers());
                                  s.bct(player.getPosition(), game.getWorld());
                              });
                return void();
            }
            else return player.getSession().send(Actor::Message::Ko);
        };
        player.startCmdTimeout("player take item", Player::Command::Duration::Take, cb);
    }

    void ManipulateResourceAction::put(Player &player, const std::string &item, Game &game) {
        auto cb = [&player, item, &game, this]() {
            auto &square = game.getWorld().getSquare(player.getPosition().x, player.getPosition().y);
            std::function<bool(const Resource &)> pred = [&item, &player](const Resource &resource) {
                return resource.getName() == item && player.getInventory().getStock(resource) > 0;
            };
            int newStock = -1;
            if (item.empty()) return player.getSession().send(Actor::Message::Ko);
            auto found = std::find_if(World::Resources::resources.begin(), World::Resources::resources.end(), pred);
            if (found != World::Resources::resources.end()) {
                auto resource = *found;
                player.getInventory().addStock(resource, newStock);
                square.addResource(resource, -newStock);
                player.getSession().send(Actor::Message::OK);
                std::for_each(game.getSpectators().begin(), game.getSpectators().end(),
                              [&player, &game, resource](Spectator &s) {
                                  s.pgr(player.getId(), game.getPlayers(), resource);
                                  s.pin(player.getId(), game.getPlayers());
                                  s.bct(player.getPosition(), game.getWorld());
                              });
                return void();
            }
            else return player.getSession().send(Actor::Message::Ko);
        };
        player.startCmdTimeout("player put item", Player::Command::Duration::Put, cb);
    }


}



