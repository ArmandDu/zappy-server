//
// Created by armanddu on 12/07/16.
//

#ifndef ZAPPY_BROADCASTACTION_H
#define ZAPPY_BROADCASTACTION_H


#include "../../ActionInterface.h"

namespace zappy {
    class BroadcastAction: public ActionInterface<Player> {

    public:
        BroadcastAction() {}

        bool isAction(const std::string &command) const;
        void trigger(Player &actor, const std::string &command, const std::string &broadcastText, Game &game);

    };
}


#endif //ZAPPY_BROADCASTACTION_H
