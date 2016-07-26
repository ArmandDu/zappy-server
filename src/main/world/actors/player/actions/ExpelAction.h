//
// Created by armanddu on 12/07/16.
//

#ifndef ZAPPY_EXPELACTION_H
#define ZAPPY_EXPELACTION_H

#include "../../ActionInterface.h"

namespace zappy {
    class ExpelAction: public ActionInterface<Player> {

    public:
        ExpelAction() {}

        bool isAction(const std::string &command) const;
        void trigger(Player &actor, const std::string &command, const std::string &args, Game &game);

    };
}


#endif //ZAPPY_EXPELACTION_H
