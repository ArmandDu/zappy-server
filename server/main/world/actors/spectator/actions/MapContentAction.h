//
// Created by armanddu on 13/07/16.
//

#ifndef ZAPPY_MAPCONTENTACTION_H
#define ZAPPY_MAPCONTENTACTION_H


#include "../../ActionInterface.h"

namespace zappy {
class MapContentAction: public ActionInterface<Spectator> {


public:
    bool isAction(const std::string &command) const;
    void trigger(Spectator &actor, const std::string &command, const std::string &args, Game &game);

private:
    void mct(Spectator &spectator, Game &game);
    void bct(Spectator &spectator, Game &game, const std::string &pos);
};
}

#endif //ZAPPY_MAPCONTENTACTION_H
