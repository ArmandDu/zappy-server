//
// Created by armanddu on 05/07/16.
//

#ifndef ZAPPY_CLIENT_GAME_H
#define ZAPPY_CLIENT_GAME_H

#include <list>
#include "world/actors/spectator/Spectator.h"
#include "world/actors/player/Player.h"
#include "world/actors/player/Team.h"

namespace zappy {
    class Game {

    private:
        std::list<Spectator> spectators;
        std::list<Player> players;
        std::vector<Team> teams;
        World world;
        int deltaTime;
        World::Fertility fertility_;

    public:
        Game(int deltaTime, const Rect &size, std::vector<std::string> teams, int capacity);

        void update();

        void disconnect(Spectator &spectator);
        void disconnect(Player &player);


    public:
        inline std::list<Spectator> &getSpectators() { return spectators; }
        inline std::list<Player> &getPlayers()  { return players; }
        inline std::vector<Team> &getTeams()  { return teams; }
        inline int getDeltaTime() const { return deltaTime; }
        inline World &getWorld()  { return world; }
        inline void addSpectator(const Spectator &spectator) { spectators.push_back(spectator); }
        inline void addPlayer(const Player &player) { players.push_back(player); }

    public:

        void setDeltaTime(int time);

        Spectator &findSpectator(const my_tcp::Client &client);
        Player &findPlayer(const my_tcp::Client &client);
        Player &findPlayer(Player &player);

        bool isSpectator(const my_tcp::Client &client) const;
        bool isPlayer(const my_tcp::Client &client) const;

        bool teamExists(std::string teamName);
        Team &findTeam(const std::string &teamName);

        Point getRelativePosition(const Player::Orientation &orientation, Point position, int dx, int dy);

    private:
        void updateTimeout(Player &player);
        void updateDeadPlayers(Player &player);
        void removeDeadPlayer(Player &player);

    };
}

#endif //ZAPPY_CLIENT_GAME_H
