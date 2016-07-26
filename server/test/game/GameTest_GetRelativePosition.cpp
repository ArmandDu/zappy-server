//
// Created by armanddu on 11/07/16.
//

#include <gtest/gtest.h>
#include "../../main/world/Rect.h"
#include "../../main/Game.h"

namespace zappy {
    class GameTest_GetRelativePosition : public ::testing::Test {

    protected:
        virtual void TearDown() {
            delete game;
        }

        virtual void SetUp() {
            game = new Game(0, zappy::Rect(10, 10, 0, 0), std::vector<std::string>(), 0);
            pos_0_0 = Point(0, 0);
            pos_5_5 = Point(5, 5);
            pos_3_1 = Point(3, 1);
        }

        Game *game;
        Point pos_0_0, pos_5_5, pos_3_1;
    };

    TEST_F(GameTest_GetRelativePosition, test_get_relative_position_north_pos_0_0) {

        /*
         *  0x0|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         *  1_0|1_1|___|___|___|___|1-1
         */
        Point pos;
        zappy::Player::Orientation orientation = zappy::Player::Orientation::North;
        pos = game->getRelativePosition(orientation, pos_0_0, 0, 0);
        ASSERT_EQ(pos.x, 0);
        ASSERT_EQ(pos.y, 0);
        pos = game->getRelativePosition(orientation, pos_0_0, 1, -1);
        ASSERT_EQ(pos.x, 9);
        ASSERT_EQ(pos.y, 9);
        pos = game->getRelativePosition(orientation, pos_0_0, 1, 0);
        ASSERT_EQ(pos.x, 0);
        ASSERT_EQ(pos.y, 9);
        pos = game->getRelativePosition(orientation, pos_0_0, 1, 1);
        ASSERT_EQ(pos.x, 1);
        ASSERT_EQ(pos.y, 9);

    }

    TEST_F(GameTest_GetRelativePosition, test_get_relative_position_north_pos_centered) {

        /*
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|1-1|1_0|1_1|___|___
         *  ___|___|___|0x0|___|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         */
        Point pos;
        zappy::Player::Orientation orientation = zappy::Player::Orientation::North;
        pos = game->getRelativePosition(orientation, pos_5_5, 0, 0);
        ASSERT_EQ(pos.x, 5);
        ASSERT_EQ(pos.y, 5);
        pos = game->getRelativePosition(orientation, pos_5_5, 0, -1);
        ASSERT_EQ(pos.x, 4);
        ASSERT_EQ(pos.y, 5);
        pos = game->getRelativePosition(orientation, pos_5_5, 1, -1);
        ASSERT_EQ(pos.x, 4);
        ASSERT_EQ(pos.y, 4);
        pos = game->getRelativePosition(orientation, pos_5_5, -1, -1);
        ASSERT_EQ(pos.x, 4);
        ASSERT_EQ(pos.y, 6);

    }

    TEST_F(GameTest_GetRelativePosition, test_get_relative_position_north_pos_x_not_y) {

        /*
         *  ___|___|1-1|1_0|1_1|___|___
         *  ___|___|___|0x0|___|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         */
        Point pos;
        zappy::Player::Orientation orientation = zappy::Player::Orientation::North;
        pos = game->getRelativePosition(orientation, pos_3_1, 0, 0);
        ASSERT_EQ(pos.x, 3);
        ASSERT_EQ(pos.y, 1);
        pos = game->getRelativePosition(orientation, pos_3_1, 1, -1);
        ASSERT_EQ(pos.x, 2);
        ASSERT_EQ(pos.y, 0);
        pos = game->getRelativePosition(orientation, pos_3_1, 1, 0);
        ASSERT_EQ(pos.x, 3);
        ASSERT_EQ(pos.y, 0);
        pos = game->getRelativePosition(orientation, pos_3_1, 1, 1);
        ASSERT_EQ(pos.x, 4);
        ASSERT_EQ(pos.y, 0);

    }

    TEST_F(GameTest_GetRelativePosition, test_get_relative_position_east_pos_0_0) {

        /*
         *  0x0|1_0|___|___|___|___|___
         *  ___|1_1|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         *  ___|1-1|___|___|___|___|___
         */
        Point pos;
        zappy::Player::Orientation orientation = zappy::Player::Orientation::East;
        pos = game->getRelativePosition(orientation, pos_0_0, 0, 0);
        ASSERT_EQ(pos.x, 0);
        ASSERT_EQ(pos.y, 0);
        pos = game->getRelativePosition(orientation, pos_0_0, 1, -1);
        ASSERT_EQ(pos.x, 1);
        ASSERT_EQ(pos.y, 9);
        pos = game->getRelativePosition(orientation, pos_0_0, 1, 0);
        ASSERT_EQ(pos.x, 1);
        ASSERT_EQ(pos.y, 0);
        pos = game->getRelativePosition(orientation, pos_0_0, 1, 1);
        ASSERT_EQ(pos.x, 1);
        ASSERT_EQ(pos.y, 1);
    }

    TEST_F(GameTest_GetRelativePosition, test_get_relative_position_east_pos_centered) {


        /*
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|1-1|___|___
         *  ___|___|___|0x0|1_0|___|___
         *  ___|___|___|___|1_1|___|___
         *  ___|___|___|___|___|___|___
         */
        Point pos;
        zappy::Player::Orientation orientation = zappy::Player::Orientation::East;
        pos = game->getRelativePosition(orientation, pos_5_5, 0, 0);
        ASSERT_EQ(pos.x, 5);
        ASSERT_EQ(pos.y, 5);
        pos = game->getRelativePosition(orientation, pos_5_5, 1, -1);
        ASSERT_EQ(pos.x, 6);
        ASSERT_EQ(pos.y, 4);
        pos = game->getRelativePosition(orientation, pos_5_5, 1, 0);
        ASSERT_EQ(pos.x, 6);
        ASSERT_EQ(pos.y, 5);
        pos = game->getRelativePosition(orientation, pos_5_5, 1, 1);
        ASSERT_EQ(pos.x, 6);
        ASSERT_EQ(pos.y, 6);
    }

    TEST_F(GameTest_GetRelativePosition, test_get_relative_position_east_pos_x_not_y) {

        /*
         *  ___|___|___|___|1-1|___|___
         *  ___|___|___|0x0|1_0|___|___
         *  ___|___|___|___|1_1|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         */
        Point pos;
        zappy::Player::Orientation orientation = zappy::Player::Orientation::East;
        pos = game->getRelativePosition(orientation, pos_3_1, 0, 0);
        ASSERT_EQ(pos.x, 3);
        ASSERT_EQ(pos.y, 1);
        pos = game->getRelativePosition(orientation, pos_3_1, 1, -1);
        ASSERT_EQ(pos.x, 4);
        ASSERT_EQ(pos.y, 0);
        pos = game->getRelativePosition(orientation, pos_3_1, 1, 0);
        ASSERT_EQ(pos.x, 4);
        ASSERT_EQ(pos.y, 1);
        pos = game->getRelativePosition(orientation, pos_3_1, 1, 1);
        ASSERT_EQ(pos.x, 4);
        ASSERT_EQ(pos.y, 2);

    }

    TEST_F(GameTest_GetRelativePosition, test_get_relative_position_south_pos_0_0) {

        /*
         *  0x0|___|___|___|___|___|___
         *  1_0|1-1|___|___|___|___|1_1
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         */
        Point pos;
        zappy::Player::Orientation orientation = zappy::Player::Orientation::South;
        pos = game->getRelativePosition(orientation, pos_0_0, 0, 0);
        ASSERT_EQ(pos.x, 0);
        ASSERT_EQ(pos.y, 0);
        pos = game->getRelativePosition(orientation, pos_0_0, 1, -1);
        ASSERT_EQ(pos.x, 1);
        ASSERT_EQ(pos.y, 1);
        pos = game->getRelativePosition(orientation, pos_0_0, 1, 0);
        ASSERT_EQ(pos.x, 0);
        ASSERT_EQ(pos.y, 1);
        pos = game->getRelativePosition(orientation, pos_0_0, 1, 1);
        ASSERT_EQ(pos.x, 9);
        ASSERT_EQ(pos.y, 1);
    }

    TEST_F(GameTest_GetRelativePosition, test_get_relative_position_south_pos_centered) {

        /*
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|___|0x0|___|___|___
         *  ___|___|1_1|1_0|1-1|___|___
         *  ___|___|___|___|___|___|___
         */
        Point pos;
        zappy::Player::Orientation orientation = zappy::Player::Orientation::South;
        pos = game->getRelativePosition(orientation, pos_5_5, 0, 0);
        ASSERT_EQ(pos.x, 5);
        ASSERT_EQ(pos.y, 5);
        pos = game->getRelativePosition(orientation, pos_5_5, 1, -1);
        ASSERT_EQ(pos.x, 6);
        ASSERT_EQ(pos.y, 6);
        pos = game->getRelativePosition(orientation, pos_5_5, 1, 0);
        ASSERT_EQ(pos.x, 5);
        ASSERT_EQ(pos.y, 6);
        pos = game->getRelativePosition(orientation, pos_5_5, 1, 1);
        ASSERT_EQ(pos.x, 4);
        ASSERT_EQ(pos.y, 6);

    }

    TEST_F(GameTest_GetRelativePosition, test_get_relative_position_south_pos_x_not_y) {

        /*
         *  ___|___|___|___|___|___|___
         *  ___|___|___|0x0|___|___|___
         *  ___|___|1_1|1_0|1-1|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         */
        Point pos;
        zappy::Player::Orientation orientation = zappy::Player::Orientation::South;
        pos = game->getRelativePosition(orientation, pos_3_1, 0, 0);
        ASSERT_EQ(pos.x, pos_3_1.x + 0);
        ASSERT_EQ(pos.y, pos_3_1.y + 0);
        pos = game->getRelativePosition(orientation, pos_3_1, 1, -1);
        ASSERT_EQ(pos.x, pos_3_1.x + 1);
        ASSERT_EQ(pos.y, pos_3_1.y + 1);
        pos = game->getRelativePosition(orientation, pos_3_1, 1, 0);
        ASSERT_EQ(pos.x, pos_3_1.x + 0);
        ASSERT_EQ(pos.y, pos_3_1.y + 1);
        pos = game->getRelativePosition(orientation, pos_3_1, 1, 1);
        ASSERT_EQ(pos.x, pos_3_1.x + -1);
        ASSERT_EQ(pos.y, pos_3_1.y + 1);

    }


    TEST_F(GameTest_GetRelativePosition, test_get_relative_position_west_pos_0_0) {

        /*
         *  0x0|___|___|___|___|___|1_0
         *  ___|___|___|___|___|___|1-1
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|1_1
         */
        Point pos;
        zappy::Player::Orientation orientation = zappy::Player::Orientation::West;
        pos = game->getRelativePosition(orientation, pos_0_0, 0, 0);
        ASSERT_EQ(pos.x, 0);
        ASSERT_EQ(pos.y, 0);
        pos = game->getRelativePosition(orientation, pos_0_0, 1, -1);
        ASSERT_EQ(pos.x, 9);
        ASSERT_EQ(pos.y, 1);
        pos = game->getRelativePosition(orientation, pos_0_0, 1, 0);
        ASSERT_EQ(pos.x, 9);
        ASSERT_EQ(pos.y, 0);
        pos = game->getRelativePosition(orientation, pos_0_0, 1, 1);
        ASSERT_EQ(pos.x, 9);
        ASSERT_EQ(pos.y, 9);
    }

    TEST_F(GameTest_GetRelativePosition, test_get_relative_position_west_pos_x_not_y) {

        /*
         *  ___|___|1_1|___|___|___|___
         *  ___|___|1_0|0x0|___|___|___
         *  ___|___|1-1|___|___|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         *  ___|___|___|___|___|___|___
         */
        Point pos;
        zappy::Player::Orientation orientation = zappy::Player::Orientation::West;
        pos = game->getRelativePosition(orientation, pos_3_1, 0, 0);
        ASSERT_EQ(pos.x, 3);
        ASSERT_EQ(pos.y, 1);
        pos = game->getRelativePosition(orientation, pos_3_1, 1, -1);
        ASSERT_EQ(pos.x, 2);
        ASSERT_EQ(pos.y, 2);
        pos = game->getRelativePosition(orientation, pos_3_1, 1, 0);
        ASSERT_EQ(pos.x, 2);
        ASSERT_EQ(pos.y, 1);
        pos = game->getRelativePosition(orientation, pos_3_1, 1, 1);
        ASSERT_EQ(pos.x, 2);
        ASSERT_EQ(pos.y, 0);
    }
}