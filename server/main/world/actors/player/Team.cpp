//
// Created by armanddu on 28/06/16.
//

#include "Team.h"
#include "Player.h"

namespace zappy {

    Team::Team(const std::string &name, int capacity) : name(name), capacity(capacity) { }

    bool Team::add(Player &player) {
        if (capacity > players.size()) {
            player.setTeamName(getName());
            players.push_back(player);
        }
        return capacity >= players.size();
    }

    void Team::quit(Player &player) { players.remove(player);}

    int Team::getCapacity() const { return (int) (capacity - players.size()); }

    std::string Team::getName() const { return name; }

    bool Team::operator<(const Team &t) const { return t.getName() < getName(); }


}






