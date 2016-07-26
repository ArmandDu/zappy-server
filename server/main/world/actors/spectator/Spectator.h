//
// Created by armanddu on 29/06/16.
//

#ifndef ZAPPY_CLIENT_SPECTATOR_H
#define ZAPPY_CLIENT_SPECTATOR_H


#include <list>
#include "../../../tcp/Client.h"
#include "../player/Player.h"
#include "../Actor.h"

namespace zappy {
    class Spectator : public Actor{

    public:

        class Message : public Actor::Message {
        public:
            static const std::string &MapSize;
            static const std::string &MessageUnknown;
            static const std::string &InvalidParams;

            static const std::string &Name;

            static const std::string &Sgt;
            static const std::string &Sst;
            static const std::string &Tna;
            static const std::string &Ppo;
            static const std::string &Plv;
            static const std::string &Pin;
            static const std::string &Bct;
            static const std::string &Mct;
            static const std::string &Pbc;
            static const std::string &Pdi;
            static const std::string &Pnw;
            static const std::string &Pgt;
            static const std::string &Pdr;
            static const std::string &Pic;
            static const std::string &Pie;
            static const std::string &Pex;
        };

    public:
        Spectator(my_tcp::Client::Session session);

    public:
        void disconnect();
    public:
        void pin(std::string playerId, std::list<Player> players) ;
        void ppo(std::string playerId, std::list<Player> players) ;
        void pnw(std::string playerId, std::list<Player> players) ;
        void pdi(std::string playerId, std::list<Player> players) ;
        void plv(std::string playerId, std::list<Player> players) ;
        void pbc(std::string playerId, std::string broadcastText) ;
        void pex(std::string playerId, std::list<Player> players) ;
        void pgt(std::string playerId, std::list<Player> players, Resource resource) ;
        void pgr(std::string playerId, std::list<Player> players, Resource resource) ;
        void bct(Point pos, World &world) ;
        void mct(World &world);

        void pic(Player &incantator, std::list<std::string> &ids, std::list<Player> &players);
        void pie(Player &incantator, bool players);

    private:
        std::string getSquareBctString(int x, int y, World &world) const;
        std::string getPlayerId(const std::string &args) const;


        bool playerExists(std::string playerId, std::list<Player> &players);

        Player &findPlayer(std::string playerId, std::list<Player> players);

    };

}

#endif //ZAPPY_CLIENT_SPECTATOR_H
