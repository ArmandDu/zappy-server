//
// Created by armanddu on 12/07/16.
//

#include <algorithm>
#include "TurnAction.h"

namespace zappy {
    bool TurnAction::isAction(const std::string &command) const {
        return isCommand(command, Player::Command::TurnLeft) ||
                isCommand(command, Player::Command::TurnRight);
    }

    void TurnAction::trigger(Player &actor, const std::string &command, const std::string &args, Game &game) {
        if (isCommand(command, Player::Command::TurnLeft)) return turn(actor, [&actor]() { actor.left(); }, "left",
                                                                       game, Player::Command::Duration::TurnLeft);
        if (isCommand(command, Player::Command::TurnRight)) return turn(actor, [&actor]() { actor.right(); },
                                                                        "right",
                                                                        game, Player::Command::Duration::TurnRight);
    }

    void TurnAction::turn(Player &player, std::function<void()> turn, const std::string direction, Game &game, double tm) {
        auto cb = [&player, turn, &game]() {
            turn();
            player.getSession().send(Player::Message::OK);
            std::for_each(game.getSpectators().begin(), game.getSpectators().end(),
                          [&player, &game](Spectator &s) {s.ppo(player.getId(), game.getPlayers());});
        };
        player.startCmdTimeout("player turn " + direction, tm, cb);
    }


}

