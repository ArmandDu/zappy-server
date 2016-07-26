//
// Created by armanddu on 14/07/16.
//

#ifndef ZAPPY_PLAYERPOSITIONORIENTATIONACTION_H
#define ZAPPY_PLAYERPOSITIONORIENTATIONACTION_H


#include "../Spectator.h"
#include "../../ActionInterface.h"

namespace zappy {
    class PlayerPositionOrientationAction : public  ActionInterface<Spectator> {


    public:
        bool isAction(const std::string &command) const;
        void trigger(Spectator &spectator, const std::string &command, const std::string &args, Game &game);

    };
}


#endif //ZAPPY_PLAYERPOSITIONORIENTATIONACTION_H
