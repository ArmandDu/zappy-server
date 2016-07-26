//
// Created by armanddu on 12/07/16.
//

#include "ForkAction.h"

//TODO FORK ACTION
namespace zappy {

    bool ForkAction::isAction(const std::string &command) const {
        return isCommand(command, Player::Command::Fork);
    }

    void ForkAction::trigger(Player &actor, const std::string &command, const std::string &args, Game &game) {}

}
