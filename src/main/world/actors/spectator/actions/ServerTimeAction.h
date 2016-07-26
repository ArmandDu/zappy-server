//
// Created by armanddu on 13/07/16.
//

#ifndef ZAPPY_SERVERTIMEACTION_H
#define ZAPPY_SERVERTIMEACTION_H


#include "../../ActionInterface.h"

namespace zappy {
    class ServerTimeAction : public ActionInterface<Spectator>{


    public:
        bool isAction(const std::string &command) const;
        void trigger(Spectator &actor, const std::string &command, const std::string &args, Game &game);

    private:
        void sgt(Spectator &spectator, Game &game);

        void sst(Spectator &spectator, const std::string &params, Game &game);
    };
}


#endif //ZAPPY_SERVERTIMEACTION_H
