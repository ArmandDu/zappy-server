//
// Created by  armanddu on 05/07/16.
//

#include <algorithm>
#include <iostream>
#include <iterator>
#include "Game.h"

namespace zappy {

    Game::Game(int deltaTime, const Rect &size, std::vector<std::string> teams, int capacity)
            : world(size), deltaTime(deltaTime), fertility_(World::Fertility::Abundant) {
        for (auto &name: teams) {
            this->teams.push_back(Team(name, capacity));
        }
        world.generateResources<World::Abundant>();
    }

    Spectator &Game::findSpectator(const my_tcp::Client &client) {
        return *std::find_if(spectators.begin(), spectators.end(),
                             [&client](Actor &s) { return s.getSession().getId() == client.getId();});
    }

    Player &Game::findPlayer(const my_tcp::Client &client) {
        return *std::find_if(players.begin(), players.end(),
                             [&client](Actor &s) { return s.getId() == client.getId();});
    }

    Player &Game::findPlayer(Player &player) {
        return findPlayer(player.getSession().getClient());
    }

    bool Game::isSpectator(const my_tcp::Client &client) const{
        return std::find_if(spectators.begin(), spectators.end(),
                            [&client](const Actor &s) { return s.getId() == client.getId();}) != spectators.end();
    }

    bool Game::isPlayer(const my_tcp::Client &client) const{
        return std::find_if(players.begin(), players.end(),
                            [&client](const Actor &s) { return s.getId() == client.getId();}) != players.end();
    }


    void Game::setDeltaTime(int time) {
        if (time > 0) deltaTime = time;
    }

    bool Game::teamExists(std::string teamName) {
        return teams.end() != std::find_if(teams.begin(), teams.end(),
                                           [teamName](Team &t) {return t.getName() == teamName;});
    }
    Team &Game::findTeam(const std::string &teamName) {
        return *std::find_if(teams.begin(), teams.end(),
                             [teamName](Team &t) {return t.getName() == teamName;});
    }


    Point Game::getRelativePosition(const Player::Orientation &orientation, Point position, int dx, int dy) {
        if (dx == 0 && dy == 0) return Point(position.x, position.y);
        int x, y;
        auto size = getWorld().getSize();
        if (orientation == Player::North) { x = position.x + dy; y =  position.y + -dx; }
        else if (orientation == Player::East) { x = position.x + dx; y =  position.y + dy; }
        else if (orientation == Player::South) { x = position.x + -dy; y = position.y + dx; }
        else /* orientation == Player::WEST */{ x = position.x + -dx; y = position.y + -dy; }
        return Point((x + size.width) % size.width, (y + size.height) % size.height);
    }

    void Game::disconnect(Spectator &spectator) {
        spectator.disconnect();
        spectators.remove(spectator);
    }
    void Game::disconnect(Player &player) {
        std::for_each(getSpectators().begin(), getSpectators().end(),
                      [&player, this](Spectator &s) {
                          s.pdi(player.getId(), getPlayers());
                      });
        if (teamExists(player.getTeamName()))
            findTeam(player.getTeamName()).quit(player);
        player.disconnect();
        players.remove(player);
    }

    void Game::update() {
        auto hasExited = [](Actor &actor) {return actor.hasExited();};
        spectators.remove_if(hasExited);
        players.remove_if(hasExited);

        std::for_each(players.begin(), players.end(), [this](Player &player) {
            updateTimeout(player);
            updateDeadPlayers(player);
            removeDeadPlayer(player);
        });
        world.generateResources<World::Abundant>();

    }

    void Game::updateTimeout(Player &player) {
        player.updateCmdTimeout(getDeltaTime());

        player.updateAppetite(getDeltaTime());
        if (!player.isBusy() && player.hasCommand()) {
            player.startCmdTimeout(player.popCommand());
        }
    }

    void Game::updateDeadPlayers(Player &player) {
        if (player.isDead(getDeltaTime()) && !player.hasExited()) {
            if (teamExists(player.getTeamName()))
                findTeam(player.getTeamName()).quit(player);
            player.getSession().send(Player::Message::deadMessage);
        }
    }

    void Game::removeDeadPlayer(Player &player) {
        if( player.isDead(getDeltaTime()) && player.hasExited()
            && player.getSession().getClient().canDisconnect()) {
            player.getSession().disconnect();
            disconnect(player);
        }
    }

}
