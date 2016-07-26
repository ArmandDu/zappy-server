//
// Created by armanddu on 14/07/16.
//

#include "PlayerLevelAction.h"

namespace zappy {

    bool PlayerLevelAction::isAction(const std::string &command) const {
        return isCommand(command, Spectator::Message::Plv);
    }

    void PlayerLevelAction::trigger(Spectator &spectator, const std::string &command,
                                    const std::string &args, Game &game) {
        spectator.plv(args, game.getPlayers());
    }


}