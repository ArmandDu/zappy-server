//
// Created by armanddu on 12/07/16.
//

#include <gtest/gtest.h>
#include "../../main/world/Rect.h"
#include "../../main/Game.h"

namespace zappy {
    class GameTest_FindEntitiesTest : public ::testing::Test {

    protected:
        GameTest_FindEntitiesTest() {}

        virtual void TearDown() {
            delete game;
        }

        virtual void SetUp() {
            auto teams = std::vector<std::string>();
            teams.push_back(team_0);
            teams.push_back(team_1);
            game = new zappy::Game(0, size, teams, 10);
//        game->addPlayer(player_0_no_team);
            game->addPlayer(player_1_team_0);
//        game->addPlayer(player_2_team_1);
//        game->addPlayer(player_4_invalid_team_name);
//        game->findTeam(team_0).add(player_1_team_0);
//        game->findTeam(team_1).add(player_2_team_1);
//        player_3_team_not_in_game.setTeamName(team_not_in_game);
//        player_4_invalid_team_name.setTeamName("invalid_team_name");
        }

        Rect size = zappy::Rect(10, 10, 0, 0);
        Game *game;
        std::string team_0 = "team_0";
        std::string team_1 = "team_1";
        std::string team_not_in_game = "team_not_in_game";
//    my_tcp::Client client_0 = zappy::Client();
        my_tcp::Client client_1 = my_tcp::Client();
//    Player player_0_no_team = zappy::Player(client_0.getSession(), size);
        Player player_1_team_0 = zappy::Player(client_1.getSession(), size, Point(), zappy::Player::Orientation::North);
//    Player player_2_team_1;
//    Player player_3_team_not_in_game;
//    Player player_4_invalid_team_name;

    };

    TEST_F(GameTest_FindEntitiesTest, test_find_player_1) {

        Player &player = game->findPlayer(player_1_team_0);
        ASSERT_EQ(player.getId(), player_1_team_0.getId());
    }

    TEST_F(GameTest_FindEntitiesTest, test_get_team_not_in_game_return_address_of_end_iterator) {

        Team &team = game->findTeam(team_not_in_game);
        ASSERT_EQ(std::addressof(team), std::addressof(*(game->getTeams().end())));
    }

    TEST_F(GameTest_FindEntitiesTest, test_get_team_0) {
        Team &team = game->findTeam(team_0);
        ASSERT_EQ(team.getName(), team_0);
        ASSERT_EQ(team.getCapacity(), 10);
    }

    TEST_F(GameTest_FindEntitiesTest, test_get_team_1) {
        Team &team = game->findTeam(team_1);
        ASSERT_EQ(team.getName(), team_1);
        ASSERT_EQ(team.getCapacity(), 10);
    }

    TEST_F(GameTest_FindEntitiesTest, test_team_0_exists) {
        ASSERT_TRUE(game->teamExists(team_0));
    }

    TEST_F(GameTest_FindEntitiesTest, test_team_1_exists) {
        ASSERT_TRUE(game->teamExists(team_1));
    }

    TEST_F(GameTest_FindEntitiesTest, test_team_not_in_game_do_not_exists) {
        ASSERT_FALSE(game->teamExists(team_not_in_game));
    }
}
