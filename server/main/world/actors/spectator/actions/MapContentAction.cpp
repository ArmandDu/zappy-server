//
// Created by armanddu on 13/07/16.
//

#include <iterator>
#include "MapContentAction.h"

namespace zappy {
    bool zappy::MapContentAction::isAction(const std::string &command) const {
        return isCommand(command, Spectator::Message::Mct) ||
               isCommand(command, Spectator::Message::Bct);
    }

    void MapContentAction::trigger(Spectator &actor, const std::string &command, const std::string &args, Game &game) {
        if (isCommand(command, Spectator::Message::Mct)) return mct(actor, game);
        if (isCommand(command, Spectator::Message::Bct)) return bct(actor, game, args);
    }

    void MapContentAction::bct(Spectator &spectator, Game &game, const std::string &pos) {
        std::istringstream iss(pos);
        std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                        std::istream_iterator<std::string>{}};
        if(tokens.size() != 2) return spectator.getSession().send(Spectator::Message::InvalidParams);
        const Rect &size = game.getWorld().getSize();
        int x = atoi(tokens.at(0).c_str());
        int y = atoi(tokens.at(1).c_str());
        return spectator.bct(Point(x, y), game.getWorld());
    }

    void MapContentAction::mct(Spectator &spectator, Game &game) {
        auto size = game.getWorld().getSize();
        for (int x = 0; x < size.width; ++x) {
            for (int y = 0; y < size.height; ++y) {
                spectator.bct(Point(x, y), game.getWorld());
            }
        }
    }


}

