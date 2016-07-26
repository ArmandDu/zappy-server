//
// Created by armanddu on 12/07/16.
//

#include <algorithm>
#include <iterator>
#include "SeeAction.h"

namespace zappy {
    bool SeeAction::isAction(const std::string &command) const {
        return isCommand(command, Player::Command::See);
    }

    void SeeAction::trigger(Player &actor, const std::string &command, const std::string &args, Game &game) {
        auto cb = [&actor, &game, this]() {
            auto message = getResources(game, actor);
            actor.getSession().send(message);
        };
        actor.startCmdTimeout("player see", Player::Command::Duration::See, cb);
    }

    std::string SeeAction::getResources(Game &game, Player &player) {
        std::string res = "{";
        Point pos = player.getPosition();
        auto level = player.getLevel();
        for (int i = 0; i <= level; ++i) {
            for (int j = -i; j <= i; ++j) {
                Point relativePosition = game.getRelativePosition(player.getOrientation(), pos, i, j);
                auto square = game.getWorld().getSquare(relativePosition.x, relativePosition.y);
                if (hasPeerPlayerOnSquare(player, relativePosition, game.getPlayers())) res += " joueur";
                std::for_each(World::Resources::resources.begin(), World::Resources::resources.end(),
                              [&res, &square](const Resource &resource){
                                  if (square.getQuantity(resource) > 0) {
                                      res +=  " " + resource.getName();
                                  }
                              });
                if (j + 1 <= i) res += ",";
            }
            if (i + 1 <= level) res += ",";
        }
        res += "}";
        return res;
    }

    bool SeeAction::hasPeerPlayerOnSquare(Player &player, Point position, const std::list<Player> &players) {
        return std::any_of(players.begin(), players.end(), [&player, &position](const Player &peer) {
            return (peer.getId() != player.getId() &&
                    peer.getPosition().x == position.x &&
                    peer.getPosition().y == position.y);
        });    }


}
