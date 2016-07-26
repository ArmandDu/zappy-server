//
// Created by armanddu on 13/07/16.
//

#ifndef ZAPPY_TNAACTION_H
#define ZAPPY_TNAACTION_H

#include "../../ActionInterface.h"

namespace zappy {
    class TeamListingAction: public ActionInterface<Spectator> {


    public:
        bool isAction(const std::string &command) const;
        void trigger(Spectator &actor, const std::string &command, const std::string &args, Game &game);
    };
}


#endif //ZAPPY_TNAACTION_H
