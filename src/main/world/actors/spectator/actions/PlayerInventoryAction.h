//
// Created by armanddu on 14/07/16.
//

#ifndef ZAPPY_PLAYERINVENTORYACTION_H
#define ZAPPY_PLAYERINVENTORYACTION_H

#include "../../ActionInterface.h"

namespace zappy {
    class PlayerInventoryAction : public  ActionInterface<Spectator> {

    public:
        bool isAction(const std::string &command) const;
        void trigger(Spectator &spectator, const std::string &command, const std::string &args, Game &game);

    };
}

#endif //ZAPPY_PLAYERINVENTORYACTION_H
