//
// Created by armanddu on 12/07/16.
//

#include <algorithm>
#include <iostream>
#include "BroadcastAction.h"

//TODO BROADCAST ACTION
namespace zappy {

    bool BroadcastAction::isAction(const std::string &command) const {
        return isCommand(command, Player::Command::Broadcast);
    }

    void BroadcastAction::trigger(Player &actor, const std::string &command, const std::string &broadcastText,
                                  Game &game) {
        auto cb = [&actor, broadcastText, &game, this]() {
            for (auto &peer: game.getPlayers()) {
                if (peer.getId() != actor.getId()) {
                    std::string message = "message " + std::to_string(peer.getAngle(actor)) + "," + broadcastText;
                    peer.getSession().send(message);
                }
            }
            actor.getSession().send(Player::Message::OK);
            std::for_each(game.getSpectators().begin(), game.getSpectators().end(),
                          [&actor, broadcastText](Spectator &s) {
                              s.pbc(actor.getId(), broadcastText);
                          });
        };
        actor.startCmdTimeout("player broadcast", Player::Command::Duration::Broadcast, cb);
    }


}



