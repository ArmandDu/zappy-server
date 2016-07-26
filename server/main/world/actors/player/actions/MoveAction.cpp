//
// Created by armanddu on 12/07/16.
//

#include <algorithm>
#include "MoveAction.h"

namespace zappy {
    bool MoveAction::isAction(const std::string &command) const {
     return isCommand(command, Player::Command::Move);
    }

    void MoveAction::trigger(Player &actor, const std::string &, const std::string &args, Game &game) {
        auto cb = [&actor, &game](){
            actor.forward();
            actor.getSession().send(Player::Message::OK);
            std::for_each(game.getSpectators().begin(), game.getSpectators().end(),
                          [&actor, &game](Spectator &s) {s.ppo(actor.getId(), game.getPlayers());});
        };
        actor.startCmdTimeout("player move", Player::Command::Duration::Move, cb);
    }


}


