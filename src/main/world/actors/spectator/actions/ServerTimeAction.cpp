//
// Created by armanddu on 13/07/16.
//

#include "ServerTimeAction.h"

namespace zappy {
    bool ServerTimeAction::isAction(const std::string &command) const {
        return isCommand(command, Spectator::Message::Sst) ||
                isCommand(command, Spectator::Message::Sgt);
    }

    void ServerTimeAction::trigger(Spectator &actor, const std::string &command, const std::string &args, Game &game) {
        if (isCommand(command, Spectator::Message::Sgt)) sgt(actor, game);
        if (isCommand(command, Spectator::Message::Sst)) sst(actor, args, game);
    }

    void ServerTimeAction::sgt(Spectator &spectator, Game &game) {
        spectator.getSession().send(Spectator::Message::Sgt + " " + std::to_string(game.getDeltaTime()));
    }

    void ServerTimeAction::sst(Spectator &spectator, const std::string &params, Game &game) {
        int deltaTime = atoi(params.c_str());
        if (deltaTime > 0) {
            game.setDeltaTime(deltaTime);
            return sgt(spectator, game);
        }
        else return spectator.getSession().send(Spectator::Message::InvalidParams);
    }


}
