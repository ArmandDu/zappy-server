//
// Created by armanddu on 14/07/16.
//

#include "PlayerInventoryAction.h"

namespace zappy {

    bool PlayerInventoryAction::isAction(const std::string &command) const {
        return isCommand(command, Spectator::Message::Pin);
    }

    void PlayerInventoryAction::trigger(Spectator &spectator, const std::string &command,
                                        const std::string &args, Game &game) {
        spectator.pin(args, game.getPlayers());
    }


}