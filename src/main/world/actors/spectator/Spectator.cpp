//
// Created by armanddu on 29/06/16.
//

#include <iostream>
#include <algorithm>
#include "Spectator.h"

namespace zappy {

    const std::string &Spectator::Message::Name = "GRAPHIC";
    const std::string &Spectator::Message::MessageUnknown = "suc";
    const std::string &Spectator::Message::InvalidParams = "sbp";

    const std::string &Spectator::Message::MapSize = "msz";
    const std::string &Spectator::Message::Sgt = "sgt";
    const std::string &Spectator::Message::Sst = "sst";
    const std::string &Spectator::Message::Tna = "tna";
    const std::string &Spectator::Message::Bct = "bct";
    const std::string &Spectator::Message::Mct = "mct";
    const std::string &Spectator::Message::Ppo = "ppo";
    const std::string &Spectator::Message::Plv = "plv";
    const std::string &Spectator::Message::Pin = "pin";
    const std::string &Spectator::Message::Pbc = "pbc";
    const std::string &Spectator::Message::Pdi = "pdi";
    const std::string &Spectator::Message::Pnw = "pnw";
    const std::string &Spectator::Message::Pgt = "pgt";
    const std::string &Spectator::Message::Pdr = "pdr";
    const std::string &Spectator::Message::Pic = "pic";
    const std::string &Spectator::Message::Pie = "pie";
    const std::string &Spectator::Message::Pex = "pex";

    Spectator::Spectator(my_tcp::Client::Session session): Actor(session) { }

    void Spectator::disconnect() {
        session.disconnect();
        exited = true;
    }

    void Spectator::ppo(std::string args, std::list<Player> players) {
        auto playerId = getPlayerId(args);
        if (!playerExists(playerId, players)) return session.send(Message::InvalidParams);
        auto player = findPlayer(playerId, players);

        std::string message = Message::Ppo + " #" + player.getId()
                              + " " + std::to_string(player.getPosition().x)
                              + " "  + std::to_string(player.getPosition().y)
                              + " " + std::to_string(player.getOrientation() + 1);
        return session.send(message);
    }

    void Spectator::pnw(std::string args, std::list<Player> players) {
        auto playerId = getPlayerId(args);
        if (!playerExists(playerId, players)) return session.send(Message::InvalidParams);
        auto player = findPlayer(playerId, players);
        std::string message = Message::Pnw + " #" + player.getId()
                              + " " + std::to_string(player.getPosition().x)
                              + " "  + std::to_string(player.getPosition().y)
                              + " " + std::to_string(player.getOrientation() + 1)
                              + " " + std::to_string(player.getLevel())
                              + " " + player.getTeamName();
        return session.send(message);
    }

    std::string Spectator::getPlayerId(const std::string &args) const {
        unsigned long find = args.find("#");
        if (args.empty())  return "";
        if (find != args.npos) return args.substr(find+1, args.npos);
        return args;
    }

    void Spectator::pgt(std::string args, std::list<Player> players, Resource resource) {
        auto playerId = getPlayerId(args);
        if (!playerExists(playerId, players)) return session.send(Message::InvalidParams);
        auto player = findPlayer(playerId, players);

        std::string message = Message::Pgt + " #" + player.getId() +
                              " " + std::to_string(resource.getId());
        return session.send(message);
    }

    void Spectator::pgr(std::string args, std::list<Player> players, Resource resource) {
        auto playerId = getPlayerId(args);
        if (!playerExists(playerId, players)) return session.send(Message::InvalidParams);
        auto player = findPlayer(playerId, players);
        std::string message = Message::Pdr + " #" + player.getId() +
                              " " + std::to_string(resource.getId());
        return session.send(message);
    }

    void Spectator::pdi(std::string args, std::list<Player> players) {
        auto playerId = getPlayerId(args);
        if (!playerExists(playerId, players)) return session.send(Message::InvalidParams);
        auto player = findPlayer(playerId, players);
        std::string message = Message::Pdi + " #" + player.getId();
        return session.send(message);
    }

    void Spectator::pex(std::string args, std::list<Player> players) {
        auto playerId = getPlayerId(args);
        if (!playerExists(playerId, players)) return session.send(Message::InvalidParams);
        auto player = findPlayer(playerId, players);
        std::string message = Message::Pex + " #" + player.getId();
        return session.send(message);
    }

    void Spectator::pbc(std::string playerId, std::string broadcastText) {
        std::string message = Message::Pbc + " #" + playerId + " " + broadcastText;
        session.send(message);
    }

    void Spectator::pin(std::string args, std::list<Player> players) {
        auto playerId = getPlayerId(args);
        if (!playerExists(playerId, players)) return session.send(Message::InvalidParams);
        auto player = findPlayer(playerId, players);
        std::string inventory = std::to_string(player.getInventory().getStock(World::Resources::Food));
        inventory += " " + std::to_string(player.getInventory().getStock(World::Resources::Linemate));
        inventory += " " + std::to_string(player.getInventory().getStock(World::Resources::Deraumere));
        inventory += " " + std::to_string(player.getInventory().getStock(World::Resources::Sibur));
        inventory += " " + std::to_string(player.getInventory().getStock(World::Resources::Mendiane));
        inventory += " " + std::to_string(player.getInventory().getStock(World::Resources::Phiras));
        inventory += " " + std::to_string(player.getInventory().getStock(World::Resources::Thystame));
        std::string message = Message::Pin + " #" + player.getId()
                              + " " + std::to_string(player.getPosition().x)
                              + " "  + std::to_string(player.getPosition().y)
                              + " " + inventory;
        return session.send(message);
    }

    void Spectator::plv(std::string args, std::list<Player> players) {
        auto playerId = getPlayerId(args);
        if (playerId.empty()) return session.send(Message::InvalidParams);
        for (auto &player: players) {
            if (player.getId() == playerId) {
                std::string message = Message::Plv + " #" + player.getId()
                                      + " " + std::to_string(player.getLevel());
                return session.send(message);
            }
        }
        return session.send(Spectator::Message::InvalidParams);
    }

    void Spectator::bct(Point pos, World &world){
        Rect size = world.getSize();
        int x = (pos.x + size.width) % size.width;
        int y = (pos.y + size.height) % size.height;
        std::string message = getSquareBctString(x, y, world);
        return session.send(message);

    }

    void Spectator::mct(World &world) {
        auto size = world.getSize();
        for (int x = 0; x < size.width; ++x) {
            for (int y = 0; y < size.height; ++y) {
                bct(Point(x, y), world);
            }
        }
    }

    std::string Spectator::getSquareBctString(int x, int y, World &world) const {
        auto &stocks = world.getSquare(x, y);
        std::string inventory = std::to_string(stocks.getQuantity(World::Resources::Food));
        inventory += " " + std::to_string(stocks.getQuantity(World::Resources::Linemate));
        inventory += " " + std::to_string(stocks.getQuantity(World::Resources::Deraumere));
        inventory += " " + std::to_string(stocks.getQuantity(World::Resources::Sibur));
        inventory += " " + std::to_string(stocks.getQuantity(World::Resources::Mendiane));
        inventory += " " + std::to_string(stocks.getQuantity(World::Resources::Phiras));
        inventory += " " + std::to_string(stocks.getQuantity(World::Resources::Thystame));
        auto message = Message::Bct  + " " + std::to_string(x) + " " + std::to_string(y) +
                       " " + inventory;
        return message;
    }

    void Spectator::pic(Player &incantator, std::list<std::string> &ids, std::list<Player> &players) {
        std::string x = std::to_string(incantator.getPosition().x);
        std::string y = std::to_string(incantator.getPosition().y);
        std::string level = std::to_string(incantator.getLevel());
        std::string message = Message::Pic + " " + x + " " + y + " " + level + " #" + incantator.getId() + " ";
        for (std::string id: ids) {
            if (playerExists(id, players) && id != incantator.getId()) {
                Player p = findPlayer(id, players);
                message += "#" + p.getId() + (p == players.back() ? "" : " ");
            }
        }
        session.send(message);
    }

    void Spectator::pie(Player &incantator, bool success) {
        std::string x = std::to_string(incantator.getPosition().x);
        std::string y = std::to_string(incantator.getPosition().y);
        std::string message = Message::Pie + " " + x + " " + y + " " + (success ? "1" : "0");
        session.send(message);
    }

    bool Spectator::playerExists(std::string playerId, std::list<Player> &players) {
        return std::any_of(players.begin(), players.end(), [playerId](Player &p) {return p.getId() == playerId;});
    }

    Player &Spectator::findPlayer(std::string playerId, std::list<Player> players) {
        return *std::find_if(players.begin(), players.end(), [playerId](Player &p) {return p.getId() == playerId;});
    }


}
