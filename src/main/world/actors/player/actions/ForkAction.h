//
// Created by armanddu on 12/07/16.
//

#ifndef ZAPPY_FORKACTION_H
#define ZAPPY_FORKACTION_H

#include "../../ActionInterface.h"

namespace zappy {
    class ForkAction: public ActionInterface<Player> {

    public:
        ForkAction() {}

        bool isAction(const std::string &command) const;
        void trigger(Player &actor, const std::string &command, const std::string &args, Game &game);

    };
}


#endif //ZAPPY_FORKACTION_H
