//
// Created by armanddu on 14/07/16.
//

#include "PlayerPositionOrientationAction.h"

namespace zappy {

    bool PlayerPositionOrientationAction::isAction(const std::string &command) const {
        return isCommand(command, Spectator::Message::Ppo);
    }

    void PlayerPositionOrientationAction::trigger(Spectator &spectator, const std::string &command,
                                        const std::string &args, Game &game) {
        spectator.ppo(args, game.getPlayers());
    }


}