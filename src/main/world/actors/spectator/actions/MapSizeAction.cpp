//
// Created by armanddu on 13/07/16.
//

#include "MapSizeAction.h"

namespace zappy {
    bool MapSizeAction::isAction(const std::string &command) const {
        return isCommand(command, Spectator::Message::MapSize);
    }

    void MapSizeAction::trigger(Spectator &actor, const std::string &command, const std::string &args, Game &game) {
        auto pos = std::to_string(game.getWorld().getSize().width);
        pos += " " + std::to_string(game.getWorld().getSize().height);
        actor.getSession().send(Spectator::Message::MapSize + " " + pos);
    }


}

