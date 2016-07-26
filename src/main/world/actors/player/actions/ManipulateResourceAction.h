//
// Created by armanddu on 12/07/16.
//

#ifndef ZAPPY_MANIPULATERESOURCEACTION_H
#define ZAPPY_MANIPULATERESOURCEACTION_H


#include "../../ActionInterface.h"

namespace zappy {
    class ManipulateResourceAction : public  ActionInterface<Player> {
    public:
        ManipulateResourceAction() {}

        bool isAction(const std::string &command) const ;
        void trigger(Player &actor, const std::string &command, const std::string &args, Game &game);


        void take(Player &player, const std::string &item, Game &game);

        void put(Player &player, const std::string &item, Game &game);

    };
}


#endif //ZAPPY_MANIPULATERESOURCEACTION_H
