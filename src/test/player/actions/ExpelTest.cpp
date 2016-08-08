//
// Created by armanddu on 25/07/16.
//

#include <gtest/gtest.h>
#include "../../../main/world/Rect.h"
#include "../../../main/world/Point.h"
#include "../../../main/Game.h"
#include "../../../main/world/actors/player/actions/ExpelAction.h"

namespace zappy {
    class ExpelTest: public ::testing::Test {

    protected:
        virtual void TearDown() {
            delete game;
            delete playerNorth;
            delete playerEast;
            delete playerSouth;
            delete playerWest;
        }

        virtual void SetUp() {
            worldSize = Rect(10, 10, 0, 0);
            pos_5_5 = Point(5, 5);


            game = new Game(0, worldSize, std::vector<std::string>(), 1);
            playerNorth = new Player(client_north.getSession(), game->getWorld().getSize(), pos_5_5, Player::Orientation::North);
            playerEast = new Player(client_east.getSession(), game->getWorld().getSize(), pos_5_5, Player::Orientation::East);
            playerSouth = new Player(client_south.getSession(), game->getWorld().getSize(), pos_5_5, Player::Orientation::South);
            playerWest = new Player(client_west.getSession(), game->getWorld().getSize(), pos_5_5, Player::Orientation::West);
            game->addPlayer(*playerNorth);
            game->addPlayer(*playerEast);
            game->addPlayer(*playerSouth);
            game->addPlayer(*playerWest);

        }

        Rect worldSize;
        Point pos_5_5;
        Game *game;
        Player *playerNorth;
        Player *playerEast;
        Player *playerSouth;
        Player *playerWest;
        my_tcp::Client client_north;
        my_tcp::Client client_east;
        my_tcp::Client client_south;
        my_tcp::Client client_west;

        ExpelAction action;

        double duration = Player::Command::Duration::Expel * 10000; //1ms = 7 * 10 zappy seconds => 0.01ms = 7 zappy second

    };


    TEST_F(ExpelTest, test_expulsor_north_north5) {
        auto expulsorOrientation  = Player::Orientation::North;
        auto playerOrientation  = Player::Orientation::North;
        auto expected = "deplacement: 5";

        my_tcp::Client client;
        Player expulsor(client.getSession(), worldSize, pos_5_5, expulsorOrientation);

        action.trigger(expulsor, "", "", *game);
        ASSERT_TRUE(expulsor.isBusy()); while (expulsor.isBusy()) expulsor.updateCmdTimeout(duration);
        ASSERT_EQ(expulsor.getSession().getClient().getOutBuffer().front(), "ok");
        std::string message = std::find_if(game->getPlayers().begin(), game->getPlayers().end(), [playerOrientation](Player &p) {
            return p.getOrientation() == playerOrientation;
        })->getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, expected);
    }

    TEST_F(ExpelTest, test_expulsor_north_east7) {
        auto expulsorOrientation  = Player::Orientation::North;
        auto playerOrientation  = Player::Orientation::East;
        auto expected = "deplacement: 7";

        my_tcp::Client client;
        Player expulsor(client.getSession(), worldSize, pos_5_5, expulsorOrientation);

        action.trigger(expulsor, "", "", *game);
        ASSERT_TRUE(expulsor.isBusy()); while (expulsor.isBusy()) expulsor.updateCmdTimeout(duration);
        ASSERT_EQ(expulsor.getSession().getClient().getOutBuffer().front(), "ok");
        std::string message = std::find_if(game->getPlayers().begin(), game->getPlayers().end(), [playerOrientation](Player &p) {
            return p.getOrientation() == playerOrientation;
        })->getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, expected);
    }

    TEST_F(ExpelTest, test_expulsor_north_south1) {
        auto expulsorOrientation  = Player::Orientation::North;
        auto playerOrientation  = Player::Orientation::South;
        auto expected = "deplacement: 1";

        my_tcp::Client client;
        Player expulsor(client.getSession(), worldSize, pos_5_5, expulsorOrientation);

        action.trigger(expulsor, "", "", *game);
        ASSERT_TRUE(expulsor.isBusy()); while (expulsor.isBusy()) expulsor.updateCmdTimeout(duration);
        ASSERT_EQ(expulsor.getSession().getClient().getOutBuffer().front(), "ok");
        std::string message = std::find_if(game->getPlayers().begin(), game->getPlayers().end(), [playerOrientation](Player &p) {
            return p.getOrientation() == playerOrientation;
        })->getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, expected);
    }

    TEST_F(ExpelTest, test_expulsor_north_west3) {
        auto expulsorOrientation  = Player::Orientation::North;
        auto playerOrientation  = Player::Orientation::West;
        auto expected = "deplacement: 3";

        my_tcp::Client client;
        Player expulsor(client.getSession(), worldSize, pos_5_5, expulsorOrientation);

        action.trigger(expulsor, "", "", *game);
        ASSERT_TRUE(expulsor.isBusy()); while (expulsor.isBusy()) expulsor.updateCmdTimeout(duration);
        ASSERT_EQ(expulsor.getSession().getClient().getOutBuffer().front(), "ok");
        std::string message = std::find_if(game->getPlayers().begin(), game->getPlayers().end(), [playerOrientation](Player &p) {
            return p.getOrientation() == playerOrientation;
        })->getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, expected);
    }



    TEST_F(ExpelTest, test_expulsor_east_north3) {
        auto expulsorOrientation  = Player::Orientation::East;
        auto playerOrientation  = Player::Orientation::North;
        auto expected = "deplacement: 3";

        my_tcp::Client client;
        Player expulsor(client.getSession(), worldSize, pos_5_5, expulsorOrientation);

        action.trigger(expulsor, "", "", *game);
        ASSERT_TRUE(expulsor.isBusy()); while (expulsor.isBusy()) expulsor.updateCmdTimeout(duration);
        ASSERT_EQ(expulsor.getSession().getClient().getOutBuffer().front(), "ok");
        std::string message = std::find_if(game->getPlayers().begin(), game->getPlayers().end(), [playerOrientation](Player &p) {
            return p.getOrientation() == playerOrientation;
        })->getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, expected);
    }

    TEST_F(ExpelTest, test_expulsor_east_east5) {
        auto expulsorOrientation  = Player::Orientation::East;
        auto playerOrientation  = Player::Orientation::East;
        auto expected = "deplacement: 5";

        my_tcp::Client client;
        Player expulsor(client.getSession(), worldSize, pos_5_5, expulsorOrientation);

        action.trigger(expulsor, "", "", *game);
        ASSERT_TRUE(expulsor.isBusy()); while (expulsor.isBusy()) expulsor.updateCmdTimeout(duration);
        ASSERT_EQ(expulsor.getSession().getClient().getOutBuffer().front(), "ok");
        std::string message = std::find_if(game->getPlayers().begin(), game->getPlayers().end(), [playerOrientation](Player &p) {
            return p.getOrientation() == playerOrientation;
        })->getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, expected);
    }

    TEST_F(ExpelTest, test_expulsor_east_south7) {
        auto expulsorOrientation  = Player::Orientation::East;
        auto playerOrientation  = Player::Orientation::South;
        auto expected = "deplacement: 7";

        my_tcp::Client client;
        Player expulsor(client.getSession(), worldSize, pos_5_5, expulsorOrientation);

        action.trigger(expulsor, "", "", *game);
        ASSERT_TRUE(expulsor.isBusy()); while (expulsor.isBusy()) expulsor.updateCmdTimeout(duration);
        ASSERT_EQ(expulsor.getSession().getClient().getOutBuffer().front(), "ok");
        Player expulsed = *std::find_if(game->getPlayers().begin(), game->getPlayers().end(), [playerOrientation](Player &p) {
            return p.getOrientation() == playerOrientation;
        });
        std::string message = expulsed.getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(expulsed.getPosition() - expulsor.getPosition(), Point(1, 0));
        ASSERT_EQ(message, expected);
    }

    TEST_F(ExpelTest, test_expulsor_east_west1) {
        auto expulsorOrientation  = Player::Orientation::East;
        auto playerOrientation  = Player::Orientation::West;
        auto expected = "deplacement: 1";

        my_tcp::Client client;
        Player expulsor(client.getSession(), worldSize, pos_5_5, expulsorOrientation);

        action.trigger(expulsor, "", "", *game);
        ASSERT_TRUE(expulsor.isBusy()); while (expulsor.isBusy()) expulsor.updateCmdTimeout(duration);
        ASSERT_EQ(expulsor.getSession().getClient().getOutBuffer().front(), "ok");
        std::string message = std::find_if(game->getPlayers().begin(), game->getPlayers().end(), [playerOrientation](Player &p) {
            return p.getOrientation() == playerOrientation;
        })->getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, expected);
    }



    TEST_F(ExpelTest, test_expulsor_south_north1) {
        auto expulsorOrientation  = Player::Orientation::South;
        auto playerOrientation  = Player::Orientation::North;
        auto expected = "deplacement: 1";

        my_tcp::Client client;
        Player expulsor(client.getSession(), worldSize, pos_5_5, expulsorOrientation);

        action.trigger(expulsor, "", "", *game);
        ASSERT_TRUE(expulsor.isBusy()); while (expulsor.isBusy()) expulsor.updateCmdTimeout(duration);
        ASSERT_EQ(expulsor.getSession().getClient().getOutBuffer().front(), "ok");
        std::string message = std::find_if(game->getPlayers().begin(), game->getPlayers().end(), [playerOrientation](Player &p) {
            return p.getOrientation() == playerOrientation;
        })->getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, expected);
    }

    TEST_F(ExpelTest, test_expulsor_south_east3) {
        auto expulsorOrientation  = Player::Orientation::South;
        auto playerOrientation  = Player::Orientation::East;
        auto expected = "deplacement: 3";

        my_tcp::Client client;
        Player expulsor(client.getSession(), worldSize, pos_5_5, expulsorOrientation);

        action.trigger(expulsor, "", "", *game);
        ASSERT_TRUE(expulsor.isBusy()); while (expulsor.isBusy()) expulsor.updateCmdTimeout(duration);
        ASSERT_EQ(expulsor.getSession().getClient().getOutBuffer().front(), "ok");
        std::string message = std::find_if(game->getPlayers().begin(), game->getPlayers().end(), [playerOrientation](Player &p) {
            return p.getOrientation() == playerOrientation;
        })->getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, expected);
    }

    TEST_F(ExpelTest, test_expulsor_south_south5) {
        auto expulsorOrientation  = Player::Orientation::South;
        auto playerOrientation  = Player::Orientation::South;
        auto expected = "deplacement: 5";

        my_tcp::Client client;
        Player expulsor(client.getSession(), worldSize, pos_5_5, expulsorOrientation);

        action.trigger(expulsor, "", "", *game);
        ASSERT_TRUE(expulsor.isBusy()); while (expulsor.isBusy()) expulsor.updateCmdTimeout(duration);
        ASSERT_EQ(expulsor.getSession().getClient().getOutBuffer().front(), "ok");
        std::string message = std::find_if(game->getPlayers().begin(), game->getPlayers().end(), [playerOrientation](Player &p) {
            return p.getOrientation() == playerOrientation;
        })->getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, expected);
    }

    TEST_F(ExpelTest, test_expulsor_south_west7) {
        auto expulsorOrientation  = Player::Orientation::South;
        auto playerOrientation  = Player::Orientation::West;
        auto expected = "deplacement: 7";

        my_tcp::Client client;
        Player expulsor(client.getSession(), worldSize, pos_5_5, expulsorOrientation);

        action.trigger(expulsor, "", "", *game);
        ASSERT_TRUE(expulsor.isBusy()); while (expulsor.isBusy()) expulsor.updateCmdTimeout(duration);
        ASSERT_EQ(expulsor.getSession().getClient().getOutBuffer().front(), "ok");
        std::string message = std::find_if(game->getPlayers().begin(), game->getPlayers().end(), [playerOrientation](Player &p) {
            return p.getOrientation() == playerOrientation;
        })->getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, expected);
    }


    TEST_F(ExpelTest, test_expulsor_west_north7) {
        auto expulsorOrientation  = Player::Orientation::West;
        auto playerOrientation  = Player::Orientation::North;
        auto expected = "deplacement: 7";

        my_tcp::Client client;
        Player expulsor(client.getSession(), worldSize, pos_5_5, expulsorOrientation);

        action.trigger(expulsor, "", "", *game);
        ASSERT_TRUE(expulsor.isBusy()); while (expulsor.isBusy()) expulsor.updateCmdTimeout(duration);
        ASSERT_EQ(expulsor.getSession().getClient().getOutBuffer().front(), "ok");
        std::string message = std::find_if(game->getPlayers().begin(), game->getPlayers().end(), [playerOrientation](Player &p) {
            return p.getOrientation() == playerOrientation;
        })->getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, expected);
    }

    TEST_F(ExpelTest, test_expulsor_west_east1) {
        auto expulsorOrientation  = Player::Orientation::West;
        auto playerOrientation  = Player::Orientation::East;
        auto expected = "deplacement: 1";

        my_tcp::Client client;
        Player expulsor(client.getSession(), worldSize, pos_5_5, expulsorOrientation);

        action.trigger(expulsor, "", "", *game);
        ASSERT_TRUE(expulsor.isBusy()); while (expulsor.isBusy()) expulsor.updateCmdTimeout(duration);
        ASSERT_EQ(expulsor.getSession().getClient().getOutBuffer().front(), "ok");
        std::string message = std::find_if(game->getPlayers().begin(), game->getPlayers().end(), [playerOrientation](Player &p) {
            return p.getOrientation() == playerOrientation;
        })->getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, expected);
    }

    TEST_F(ExpelTest, test_expulsor_west_south3) {
        auto expulsorOrientation  = Player::Orientation::West;
        auto playerOrientation  = Player::Orientation::South;
        auto expected = "deplacement: 3";

        my_tcp::Client client;
        Player expulsor(client.getSession(), worldSize, pos_5_5, expulsorOrientation);

        action.trigger(expulsor, "", "", *game);
        ASSERT_TRUE(expulsor.isBusy()); while (expulsor.isBusy()) expulsor.updateCmdTimeout(duration);
        ASSERT_EQ(expulsor.getSession().getClient().getOutBuffer().front(), "ok");
        std::string message = std::find_if(game->getPlayers().begin(), game->getPlayers().end(), [playerOrientation](Player &p) {
            return p.getOrientation() == playerOrientation;
        })->getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, expected);
    }

    TEST_F(ExpelTest, test_expulsor_west_west5) {
        auto expulsorOrientation  = Player::Orientation::West;
        auto playerOrientation  = Player::Orientation::West;
        auto expected = "deplacement: 5";

        my_tcp::Client client;
        Player expulsor(client.getSession(), worldSize, pos_5_5, expulsorOrientation);

        action.trigger(expulsor, "", "", *game);
        ASSERT_TRUE(expulsor.isBusy()); while (expulsor.isBusy()) expulsor.updateCmdTimeout(duration);
        ASSERT_EQ(expulsor.getSession().getClient().getOutBuffer().front(), "ok");
        std::string message = std::find_if(game->getPlayers().begin(), game->getPlayers().end(), [playerOrientation](Player &p) {
            return p.getOrientation() == playerOrientation;
        })->getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, expected);
    }

}