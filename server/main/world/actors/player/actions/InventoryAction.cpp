//
// Created by armanddu on 12/07/16.
//

#include "InventoryAction.h"

namespace zappy {

    bool InventoryAction::isAction(const std::string &command) const {
        return isCommand(command, Player::Command::Inventory);
    }

    void InventoryAction::trigger(Player &actor, const std::string &command, const std::string &args,
                                  Game &game) {
        auto cb = [&actor, &game]() {
            std::string inventory;
            inventory << actor.getInventory();
            actor.getSession().send(inventory);
        };
        actor.startCmdTimeout("player inventory", Player::Command::Duration::Inventory, cb);
    }


}


