//
// Created by armanddu on 22/07/16.
//

#include <gtest/gtest.h>
#include "../../../main/world/actors/player/actions/BroadcastAction.h"

namespace zappy {
    class BroadcastTest : public ::testing::Test {

    protected:
        virtual void TearDown() {
            delete game;
            delete broadcaster;
        }

        virtual void SetUp() {
            worldSize = Rect(10, 10, 0, 0);
            const Point position = Point(0, 0);
            pos_1_0 = Point(1, 0);
            pos_1_1 = Point(1, 1);
            game = new Game(0, worldSize, std::vector<std::string>(), 1);
            broadcaster = new Player(client0.getSession(), game->getWorld().getSize(), position, Player::Orientation::East);

        }

        Rect worldSize;
        Point pos_1_1, pos_1_0;
        Game *game;
        Player *broadcaster;
        my_tcp::Client client0;

        double duration = Player::Command::Duration::Broadcast * 10000; //1ms = 7 * 10 zappy seconds => 0.01ms = 7 zappy second

    };




    TEST_F(BroadcastTest, broadcast_same_square_says_position_0) {
        BroadcastAction action;

        my_tcp::Client client1;
        Player receiver = Player(client1.getSession(), game->getWorld().getSize(), Point(), Player::Orientation::East);

        game->addPlayer(receiver);

        ASSERT_EQ(game->getPlayers().size(), 1);
        ASSERT_EQ(game->getPlayers().front().getId(), receiver.getId());
        action.trigger(*broadcaster, "broadcast", "message", *game);
        ASSERT_TRUE(broadcaster->isBusy());
        while (broadcaster->isBusy()) broadcaster->updateCmdTimeout(duration);
        std::string message = game->getPlayers().back().getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, "message 0,message");
    }

    TEST_F(BroadcastTest, broadcast_touch_peer_from_the_north_return_position_1) {
        BroadcastAction action;

        my_tcp::Client client1;
        Player receiver = Player(client1.getSession(), game->getWorld().getSize(), pos_1_0, Player::Orientation::West);

        game->addPlayer(receiver);

        ASSERT_EQ(game->getPlayers().size(), 1);
        ASSERT_EQ(game->getPlayers().front().getId(), receiver.getId());
        action.trigger(*broadcaster, "broadcast", "message", *game);
        ASSERT_TRUE(broadcaster->isBusy());
        while (broadcaster->isBusy()) broadcaster->updateCmdTimeout(duration);
        std::string message = game->getPlayers().back().getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, "message 1,message");
    }

    TEST_F(BroadcastTest, broadcast_touch_peer_from_the_north_west_return_position_2) {
        BroadcastAction action;

        my_tcp::Client client1;
        Player receiver = Player(client1.getSession(), game->getWorld().getSize(),pos_1_1, Player::Orientation::North);

        game->addPlayer(receiver);

        ASSERT_EQ(game->getPlayers().size(), 1);
        ASSERT_EQ(game->getPlayers().front().getId(), receiver.getId());
        action.trigger(*broadcaster, "broadcast", "message", *game);
        ASSERT_TRUE(broadcaster->isBusy());
        while (broadcaster->isBusy()) broadcaster->updateCmdTimeout(duration);
        std::string message = game->getPlayers().back().getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, "message 2,message");
    }

    TEST_F(BroadcastTest, broadcast_touch_peer_from_the_west_return_position_3) {
        BroadcastAction action;

        my_tcp::Client client1;
        Player receiver = Player(client1.getSession(), game->getWorld().getSize(), pos_1_0, Player::Orientation::North);

        game->addPlayer(receiver);

        ASSERT_EQ(game->getPlayers().size(), 1);
        ASSERT_EQ(game->getPlayers().front().getId(), receiver.getId());
        action.trigger(*broadcaster, "broadcast", "message", *game);
        ASSERT_TRUE(broadcaster->isBusy());
        while (broadcaster->isBusy()) broadcaster->updateCmdTimeout(duration);
        std::string message = game->getPlayers().back().getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, "message 3,message");
    }

    TEST_F(BroadcastTest, broadcast_touch_peer_from_the_south_west_return_position_4) {
        BroadcastAction action;

        my_tcp::Client client1;
        Player receiver = Player(client1.getSession(), game->getWorld().getSize(), pos_1_1, Player::Orientation::East);

        game->addPlayer(receiver);

        ASSERT_EQ(game->getPlayers().size(), 1);
        ASSERT_EQ(game->getPlayers().front().getId(), receiver.getId());
        action.trigger(*broadcaster, "broadcast", "message", *game);
        ASSERT_TRUE(broadcaster->isBusy());
        while (broadcaster->isBusy()) broadcaster->updateCmdTimeout(duration);
        std::string message = game->getPlayers().back().getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, "message 4,message");
    }

    TEST_F(BroadcastTest, broadcast_touch_peer_from_the_south_return_position_5) {
        BroadcastAction action;

        my_tcp::Client client1;
        Player receiver = Player(client1.getSession(), game->getWorld().getSize(), pos_1_0, Player::Orientation::East);

        game->addPlayer(receiver);

        ASSERT_EQ(game->getPlayers().size(), 1);
        ASSERT_EQ(game->getPlayers().front().getId(), receiver.getId());
        action.trigger(*broadcaster, "broadcast", "message", *game);
        ASSERT_TRUE(broadcaster->isBusy());
        while (broadcaster->isBusy()) broadcaster->updateCmdTimeout(duration);
        std::string message = game->getPlayers().back().getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, "message 5,message");
    }

    TEST_F(BroadcastTest, broadcast_touch_peer_from_the_south_east_return_position_6) {
        BroadcastAction action;

        my_tcp::Client client1;
        Player receiver = Player(client1.getSession(), game->getWorld().getSize(), pos_1_1, Player::Orientation::South);

        game->addPlayer(receiver);

        ASSERT_EQ(game->getPlayers().size(), 1);
        ASSERT_EQ(game->getPlayers().front().getId(), receiver.getId());
        action.trigger(*broadcaster, "broadcast", "message", *game);
        ASSERT_TRUE(broadcaster->isBusy());
        while (broadcaster->isBusy()) broadcaster->updateCmdTimeout(duration);
        std::string message = game->getPlayers().back().getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, "message 6,message");
    }

    TEST_F(BroadcastTest, broadcast_touch_peer_from_the_east_return_position_7) {
        BroadcastAction action;
        
        my_tcp::Client client1;
        Player receiver = Player(client1.getSession(), game->getWorld().getSize(), pos_1_0, Player::Orientation::South);

        game->addPlayer(receiver);

        ASSERT_EQ(game->getPlayers().size(), 1);
        ASSERT_EQ(game->getPlayers().front().getId(), receiver.getId());
        action.trigger(*broadcaster, "broadcast", "message", *game);
        ASSERT_TRUE(broadcaster->isBusy());
        while (broadcaster->isBusy()) broadcaster->updateCmdTimeout(duration);
        std::string message = game->getPlayers().back().getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, "message 7,message");
    }

    TEST_F(BroadcastTest, broadcast_touch_peer_from_the_north_east_return_position_8) {
        BroadcastAction action;

        my_tcp::Client client1;
        Player receiver = Player(client1.getSession(), game->getWorld().getSize(), pos_1_1, Player::Orientation::West);

        game->addPlayer(receiver);

        ASSERT_EQ(game->getPlayers().size(), 1);
        ASSERT_EQ(game->getPlayers().front().getId(), receiver.getId());
        action.trigger(*broadcaster, "broadcast", "message", *game);
        ASSERT_TRUE(broadcaster->isBusy());
        while (broadcaster->isBusy()) broadcaster->updateCmdTimeout(duration);
        std::string message = game->getPlayers().back().getSession().getClient().getOutBuffer().front();
        ASSERT_EQ(message, "message 8,message");
    }

}