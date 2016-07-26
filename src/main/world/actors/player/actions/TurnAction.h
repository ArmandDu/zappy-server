//
// Created by armanddu on 12/07/16.
//

#ifndef ZAPPY_TURNACTION_H
#define ZAPPY_TURNACTION_H

#include "../../ActionInterface.h"

namespace zappy {
    class TurnAction : public ActionInterface<Player> {

    public:
        TurnAction() {}

        bool isAction(const std::string &command) const;
        void trigger(Player &actor, const std::string &command, const std::string &args, Game &game);

    private:
        void turn(Player &player, std::function<void()> turn, const std::string direction, Game &game, double tm);
    };
}

#endif //ZAPPY_TURNACTION_H
