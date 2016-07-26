//
// Created by armanddu on 14/07/16.
//

#ifndef ZAPPY_PLAYERSPAWNACTION_H
#define ZAPPY_PLAYERSPAWNACTION_H


#include "../../ActionInterface.h"

namespace zappy {
    class PlayerSpawnAction : public ActionInterface<Spectator> {

    public:
        bool isAction(const std::string &command) const;
        void trigger(Spectator &spectator, const std::string &command, const std::string &playerId, Game &game);

    };


}
#endif //ZAPPY_PLAYERSPAWNACTION_H
