//
// Created by armanddu on 12/07/16.
//

#ifndef ZAPPY_SEEACTION_H
#define ZAPPY_SEEACTION_H

#include "../../ActionInterface.h"

namespace  zappy {
    class SeeAction: public ActionInterface<Player> {

    public:

        SeeAction() {}

        bool isAction(const std::string &command) const;
        void trigger(Player &actor, const std::string &command, const std::string &args, Game &game);


        std::string getResources(Game &game, Player &player);

        bool hasPeerPlayerOnSquare(Player &player, Point position, const std::list<Player> &players);
    };

}

#endif //ZAPPY_SEEACTION_H
