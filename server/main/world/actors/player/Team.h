//
// Created by armanddu on 28/06/16.
//

#ifndef ZAPPY_CLIENT_TEAM_H
#define ZAPPY_CLIENT_TEAM_H


#include <set>
#include <string>
#include "Player.h"

namespace zappy {

    class Team {

    private:
        std::string name;
        int capacity;
        std::list<Player> players;

    public:
        Team(const std::string &name, int capacity);
        Team(): Team("", -1) { }

    public:
        bool add(Player &player);
        void quit(Player &player);
        int getCapacity() const;
        std::string getName() const;

    public:
        bool operator<(const Team &t) const;


    };

}

#endif //ZAPPY_CLIENT_TEAM_H
