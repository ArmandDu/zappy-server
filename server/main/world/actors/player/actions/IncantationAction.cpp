//
// Created by armanddu on 12/07/16.
//

#include <algorithm>
#include <iostream>
#include "IncantationAction.h"

namespace zappy {


    IncantationAction::IncantationRequirement::IncantationRequirement(const int level, const int nPlayers,
                                                                      const std::map<Resource, int> resources) :
            level_(level), minPlayers_(nPlayers), resources_(resources){
    }

    const int IncantationAction::IncantationRequirement::getLevel() const {
        return level_;
    }

    const int IncantationAction::IncantationRequirement::getMinPlayers() const {
        return minPlayers_;
    }

    const std::map<Resource, int> & IncantationAction::IncantationRequirement::getResources() const {
        return resources_;
    }

    IncantationAction::IncantationAction() {
        requirements.push_back(IncantationRequirement(1, 1, {{World::Resources::Linemate, 1},
                                                             {World::Resources::Deraumere, 0},
                                                             {World::Resources::Sibur, 0},
                                                             {World::Resources::Mendiane, 0},
                                                             {World::Resources::Phiras, 0},
                                                             {World::Resources::Thystame, 0}}));

        requirements.push_back(IncantationRequirement(2, 2, {{World::Resources::Linemate, 1},
                                                             {World::Resources::Deraumere, 1},
                                                             {World::Resources::Sibur, 1},
                                                             {World::Resources::Mendiane, 0},
                                                             {World::Resources::Phiras, 0},
                                                             {World::Resources::Thystame, 0}}));

        requirements.push_back(IncantationRequirement(3, 2, {{World::Resources::Linemate, 2},
                                                             {World::Resources::Deraumere, 0},
                                                             {World::Resources::Sibur, 1},
                                                             {World::Resources::Mendiane, 0},
                                                             {World::Resources::Phiras, 2},
                                                             {World::Resources::Thystame, 0}}));

        requirements.push_back(IncantationRequirement(4, 4, {{World::Resources::Linemate, 1},
                                                             {World::Resources::Deraumere, 1},
                                                             {World::Resources::Sibur, 2},
                                                             {World::Resources::Mendiane, 0},
                                                             {World::Resources::Phiras, 1},
                                                             {World::Resources::Thystame, 0}}));

        requirements.push_back(IncantationRequirement(5, 4, {{World::Resources::Linemate, 1},
                                                             {World::Resources::Deraumere, 2},
                                                             {World::Resources::Sibur, 1},
                                                             {World::Resources::Mendiane, 3},
                                                             {World::Resources::Phiras, 0},
                                                             {World::Resources::Thystame, 0}}));

        requirements.push_back(IncantationRequirement(6, 6, {{World::Resources::Linemate, 1},
                                                             {World::Resources::Deraumere, 2},
                                                             {World::Resources::Sibur, 3},
                                                             {World::Resources::Mendiane, 0},
                                                             {World::Resources::Phiras, 1},
                                                             {World::Resources::Thystame, 0}}));

        requirements.push_back(IncantationRequirement(7, 6, {{World::Resources::Linemate, 2},
                                                             {World::Resources::Deraumere, 2},
                                                             {World::Resources::Sibur, 2},
                                                             {World::Resources::Mendiane, 2},
                                                             {World::Resources::Phiras, 2},
                                                             {World::Resources::Thystame, 1}}));

    }

    bool IncantationAction::isAction(const std::string &command) const {
        return isCommand(command, Player::Command::Incantation);
    }

    void IncantationAction::trigger(Player &incantator, const std::string &command, const std::string &args, Game &game) {
        std::list<std::string> incantablePlayersIds = getIncantablePlayersId(incantator, game);
        Point position = incantator.getPosition();
        Square &square = game.getWorld().getSquare(position.x, position.y);

        broadcastStartIncantation(incantator, game, incantablePlayersIds);
        startIncantation(incantator, incantablePlayersIds, game, square);


    }

    void IncantationAction::startIncantation(Player &incantator,
                                             const std::list<std::string> &incantablePlayers,
                                             Game &game,
                                             Square &square) {

        auto cb = [&incantator, &incantablePlayers, this, &game, &square](Player &player) {
            if (isToLevelUp(incantablePlayers, player)) {
                levelUp(incantator, game, square, incantablePlayers, player);
            }
        };
        std::for_each(game.getPlayers().begin(), game.getPlayers().end(), cb);
    }

    void IncantationAction::levelUp(Player &incantator, Game &game, Square &square,
                                    const std::list<std::string> &incantablePlayers, Player &player) {
        int level = incantator.getLevel();
        player.getSession().send("elevation en cours");
        player.setIncanting(true);
        bool validRequirements = hasRequirements(level, incantablePlayers.size(), square);
        auto cb = [&player, &incantator, incantablePlayers, this, &game, &square, level, validRequirements]() {
            if (validRequirements) {
                player.levelUp();
                if (player.getId() == incantablePlayers.back()){
                    removeItems(level, square);
                }
            }
            player.getSession().send("niveau actuel : " + std::to_string(player.getLevel()));
            if (player.getId() == incantablePlayers.back())
                broadcastEndIncantation(incantator, level != player.getLevel(), game, incantablePlayers);
            player.setIncanting(false);
        };
        player.startCmdTimeout("incantation", Player::Command::Duration::Incantation, cb,
                               Player::Command::Priority::Absolute);
    }

    bool IncantationAction::isToLevelUp(const std::list<std::string> &incantablePlayers, const Player &player) const {
        return !player.isIncanting() && any_of(incantablePlayers.begin(), incantablePlayers.end(), [&player](std::string id) {
            return id == player.getId();
        });
    }

    void IncantationAction::broadcastStartIncantation(Player &incantator, Game &game, std::list<std::string> ids) const {
        for_each(game.getSpectators().begin(), game.getSpectators().end(),
                 [&game, &incantator, &ids](Spectator &s) { s.pic(incantator, ids, game.getPlayers());});
    }

    bool IncantationAction::hasRequirements(int level, long count, Square &square) {
        return std::any_of(requirements.begin(), requirements.end(), [this, level, count, &square](IncantationRequirement requirement) {
            return (requirement.getLevel() == level && requirement.getMinPlayers() <= count && hasResources(requirement.getResources(), square));
        });
    }

    std::list<std::string> IncantationAction::getIncantablePlayersId(Player &incantator, Game &game) {
        std::list<Player> players;
        std::list<std::string> result;
        std::copy_if(game.getPlayers().begin(), game.getPlayers().end(), std::back_inserter(players),
                     [&incantator](Player &p){
                         return p.getLevel() == incantator.getLevel() &&
                                p.getPosition() == incantator.getPosition();
                     });
        result.resize(players.size());
        std::transform(players.begin(), players.end(), result.begin(), [](Player &p){return p.getId();});
        return result;
    }

    void IncantationAction::broadcastEndIncantation(Player &incantator, bool success, Game &game,
                                                    const std::list<std::string> &incantablePlayers) {
        for_each(game.getSpectators().begin(), game.getSpectators().end(),
                 [&incantablePlayers, &incantator, &game, success](Spectator &spectator) {
                     spectator.pie(incantator, success);
                     std::for_each(incantablePlayers.begin(), incantablePlayers.end(), [&spectator, &game](std::string id) {
                         spectator.plv(id, game.getPlayers());
                     });
                     spectator.mct(game.getWorld());
                 });
    }

    bool IncantationAction::hasResources(const std::map<Resource, int> resources, Square &square) {
        return std::all_of(resources.begin(), resources.end(),
                           [&square](const std::pair<Resource, int> resource) {
                               return square.getQuantity(resource.first) >= resource.second;
                           });
    }

    void IncantationAction::removeItems(int level, Square &square) {
        auto found = std::find_if(requirements.begin(), requirements.end(), [level](IncantationRequirement &r) {
            return r.getLevel() == level;
        });
        if (found != requirements.end()) std::for_each(found->getResources().begin(),
                                                       found->getResources().end(),
                                                       [&square](const std::pair<Resource, int> &resource) {
                                                           square.addResource(resource.first, -resource.second);
                                                       });
    }

}
