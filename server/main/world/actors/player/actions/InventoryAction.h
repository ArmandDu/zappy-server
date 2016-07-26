//
// Created by armanddu on 12/07/16.
//

#ifndef ZAPPY_INVENTORYACTION_H
#define ZAPPY_INVENTORYACTION_H


#include "../../ActionInterface.h"

namespace zappy {
    class InventoryAction: public ActionInterface<Player> {

    public:
        InventoryAction() {}

        bool isAction(const std::string &command) const;
        void trigger(Player &actor, const std::string &command, const std::string &args, Game &game);

    };
}


#endif //ZAPPY_INVENTORYACTION_H
