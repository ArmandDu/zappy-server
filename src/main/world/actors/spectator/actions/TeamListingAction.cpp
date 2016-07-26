//
// Created by armanddu on 13/07/16.
//

#include "TeamListingAction.h"

namespace zappy {

    bool TeamListingAction::isAction(const std::string &command) const {
        return isCommand(command, Spectator::Message::Tna);
    }

    void TeamListingAction::trigger(Spectator &actor, const std::string &command, const std::string &args, Game &game) {
        for (auto &team: game.getTeams()) {
            actor.getSession().send(Spectator::Message::Tna + " " + team.getName());
        }
    }


}


