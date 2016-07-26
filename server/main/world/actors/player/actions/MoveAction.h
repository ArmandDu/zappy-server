//
// Created by armanddu on 12/07/16.
//

#ifndef ZAPPY_MOVEACTION_H
#define ZAPPY_MOVEACTION_H

#include "../../ActionInterface.h"

namespace zappy {
    class MoveAction : public ActionInterface<Player> {

    public:
        MoveAction() {}

        bool isAction(const std::string &command) const;
        void trigger(Player &actor, const std::string &command, const std::string &args, Game &game);

    };

}


#endif //ZAPPY_MOVEACTION_H
