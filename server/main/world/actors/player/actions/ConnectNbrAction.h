//
// Created by armanddu on 12/07/16.
//

#ifndef ZAPPY_CONNECTNBRACTION_H
#define ZAPPY_CONNECTNBRACTION_H

#include "../../ActionInterface.h"

namespace zappy {
    class ConnectNbrAction : public ActionInterface<Player> {

    public:
        ConnectNbrAction() {}

        bool isAction(const std::string &command) const;
        void trigger(Player &actor, const std::string &command, const std::string &args, Game &game);

    };

}


#endif //ZAPPY_CONNECTNBRACTION_H
