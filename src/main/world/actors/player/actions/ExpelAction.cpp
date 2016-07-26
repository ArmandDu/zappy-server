//
// Created by armanddu on 12/07/16.
//

#include <algorithm>
#include "ExpelAction.h"

//TODO EXPEL ACTION
namespace zappy {

    bool ExpelAction::isAction(const std::string &command) const {
        return isCommand(command, Player::Command::Expel);
    }

    void ExpelAction::trigger(Player &actor, const std::string &command, const std::string &args, Game &game) {
        auto cb = [&actor, &game, this]() {
            if (!std::any_of(game.getPlayers().begin(), game.getPlayers().end(), [&actor](Player &player){
                return  player.getId() != actor.getId() &&
                        player.getPosition() == actor.getPosition();
            })) return actor.getSession().send(Player::Message::Ko);
            std::for_each(game.getSpectators().begin(), game.getSpectators().end(), [&actor, &game](Spectator &spectator) {
                spectator.pex(actor.getId(), game.getPlayers());
            });
            std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [&actor, &game, this](Player &player) {
                if (player.getPosition() == actor.getPosition() && player.getId() != actor.getId()) {
                    player.forward(actor.getOrientation());
                    player.getSession().send("deplacement: " + std::to_string(player.getAngle(actor)));
                    std::for_each(game.getSpectators().begin(), game.getSpectators().end(), [&player, &game](Spectator &spectator) {
                        spectator.ppo(player.getId(), game.getPlayers());
                    });
                }
            });
            actor.getSession().send(Player::Message::OK);
        };
        actor.startCmdTimeout(Player::Command::Expel, Player::Command::Duration::Expel, cb);
    }


}


