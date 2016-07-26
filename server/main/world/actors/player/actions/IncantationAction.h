//
// Created by armanddu on 12/07/16.
//

#ifndef ZAPPY_INCANTATIONACTION_H
#define ZAPPY_INCANTATIONACTION_H

#include "../../ActionInterface.h"

namespace zappy {
    class IncantationAction: public ActionInterface<Player> {

    public:
        class IncantationRequirement {
        private:
            const int level_;
            const int minPlayers_;
            const std::map<Resource, int> resources_;
        public:
            IncantationRequirement(const int level, int nPlayers, const std::map<Resource, int> resources);
        public:
            const int getLevel() const;
            const int getMinPlayers() const;
            const std::map<Resource, int> & getResources() const;
        };

    private:
        std::vector<IncantationRequirement> requirements;

    public:
        IncantationAction();

        bool isAction(const std::string &command) const;
        void trigger(Player &actor, const std::string &command, const std::string &args, Game &game);

        bool hasRequirements(int level, long count, Square &square);

        void broadcastStartIncantation(Player &incantator, Game &game, std::list<std::string> ids) const;

        void startIncantation(Player &incantator, const std::list<std::string> &incantablePlayers, Game &game,
                                      Square &square);

        std::list<std::string> getIncantablePlayersId(Player &player, Game &game);

        void broadcastEndIncantation(Player &player, bool success, Game &game, const std::list<std::string> &incantablePlayers);

        bool isToLevelUp(const std::list<std::string> &incantablePlayers, const Player &player) const;

        void levelUp(Player &incantator, Game &game, Square &square, const std::list<std::string> &incantablePlayers,
                 Player &player);

        void removeItems(int level, Square &square);

        bool hasResources(const std::map<Resource, int> resources, Square &square);
    };
}


#endif //ZAPPY_INCANTATIONACTION_H
