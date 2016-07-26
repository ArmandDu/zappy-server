//
// Created by armanddu on 14/07/16.
//

#include "PlayerSpawnAction.h"

namespace zappy {
    bool zappy::PlayerSpawnAction::isAction(const std::string &command) const {
        return isCommand(command, Spectator::Message::Pnw);
    }

    void PlayerSpawnAction::trigger(Spectator &spectator, const std::string &command, const std::string &playerId, Game &game) {
        spectator.pnw(playerId, game.getPlayers());
    }


}
