//
// Created by armanddu on 12/07/16.
//

#include <algorithm>
#include "ConnectNbrAction.h"

namespace zappy {
    bool ConnectNbrAction::isAction(const std::string &command) const {
     return isCommand(command, Player::Command::ConnectNbr);
    }

    void ConnectNbrAction::trigger(Player &actor, const std::string &, const std::string &args, Game &game) {
        auto cb = [&actor, &game](){
            auto message = std::to_string(game.findTeam(actor.getTeamName()).getCapacity());
            actor.getSession().send(message);
        };
        actor.startCmdTimeout("connect_nbr", Player::Command::Duration::ConnectNbr, cb);
    }


}


