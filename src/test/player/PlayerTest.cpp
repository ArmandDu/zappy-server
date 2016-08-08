//
// Created by armanddu on 22/07/16.
//

#include <gtest/gtest.h>
#include "../../main/world/actors/player/Player.h"

namespace zappy {
    class PlayerTest : public ::testing::Test {


    protected:
        Rect size = Rect(5, 5, 0, 0);
        my_tcp::Client client;
        Player::Orientation north = Player::Orientation::North;
        Player::Orientation south = Player::Orientation::South;
        Player::Orientation east = Player::Orientation::East;
        Player::Orientation west = Player::Orientation::West;
        Point pos_0_0 = Point(0, 0);
        Point pos_2_2 = Point(2, 2);
        Point pos_2_3 = Point(2, 3);
        Point pos_3_2 = Point(3, 2);
        Point pos_0_4 = Point(0, 4);
        Point pos_4_0 = Point(4, 0);

    };


    TEST_F(PlayerTest, player_turn_left_of_north_is_west) {
        Player player(client.getSession(), size, pos_0_0, north);
        player.left();
        ASSERT_EQ(west, player.getOrientation());
    }

    TEST_F(PlayerTest, player_turn_left_of_west_is_south) {
        Player player(client.getSession(), size, pos_0_0, west);
        player.left();
        ASSERT_EQ(south, player.getOrientation());
    }

    TEST_F(PlayerTest, player_turn_left_of_south_is_east) {
        Player player(client.getSession(), size, pos_0_0, south);
        player.left();
        ASSERT_EQ(east, player.getOrientation());
    }

    TEST_F(PlayerTest, player_turn_left_of_east_is_north) {
        Player player(client.getSession(), size, pos_0_0, east);
        player.left();
        ASSERT_EQ(north, player.getOrientation());
    }

    TEST_F(PlayerTest, player_turn_right_of_north_is_east) {
        Player player(client.getSession(), size, pos_0_0, north);
        player.right();
        ASSERT_EQ(east, player.getOrientation());
    }

    TEST_F(PlayerTest, player_turn_right_of_west_is_north) {
        Player player(client.getSession(), size, pos_0_0, west);
        player.right();
        ASSERT_EQ(north, player.getOrientation());
    }

    TEST_F(PlayerTest, player_turn_right_of_south_is_west) {
        Player player(client.getSession(), size, pos_0_0, south);
        player.right();
        ASSERT_EQ(west, player.getOrientation());
    }

    TEST_F(PlayerTest, player_turn_right_of_east_is_south) {
        Player player(client.getSession(), size, pos_0_0, east);
        player.right();
        ASSERT_EQ(south, player.getOrientation());
    }

    TEST_F(PlayerTest, player_contruction_position_and_orientation_are_set) {
        Player player(client.getSession(), size, pos_0_0, north);
        ASSERT_EQ(pos_0_0, player.getPosition());
        ASSERT_EQ(north, player.getOrientation());
    }


    TEST_F(PlayerTest, player_forward_north_test_move_in_y_axis_using_modulo) {
        Player player(client.getSession(), size, pos_0_0, north);
        player.forward();
        ASSERT_EQ(Point(0, size.height-1), player.getPosition());
        ASSERT_EQ(north, player.getOrientation());
    }

    TEST_F(PlayerTest, player_forward_north_test_move_in_y_axis) {
        Player player(client.getSession(), size, pos_2_2, north);
        player.forward();
        ASSERT_EQ(Point(2, 1), player.getPosition());
        ASSERT_EQ(north, player.getOrientation());
    }

    TEST_F(PlayerTest, player_forward_south_test_move_in_y_axis_using_modulo) {
        Player player(client.getSession(), size, pos_0_4, south);
        player.forward();
        ASSERT_EQ(pos_0_0, player.getPosition());
        ASSERT_EQ(south, player.getOrientation());
    }

    TEST_F(PlayerTest, player_forward_south_test_move_in_y_axis) {
        Player player(client.getSession(), size, pos_2_2, south);
        player.forward();
        ASSERT_EQ(pos_2_3, player.getPosition());
        ASSERT_EQ(south, player.getOrientation());
    }


    TEST_F(PlayerTest, player_forward_east_test_move_in_x_axis_using_modulo) {
        Player player(client.getSession(), size, pos_4_0, east);
        player.forward();
        ASSERT_EQ(pos_0_0, player.getPosition());
        ASSERT_EQ(east, player.getOrientation());
    }

    TEST_F(PlayerTest, player_forward_east_test_move_in_x_axis) {
        Player player(client.getSession(), size, pos_2_2, east);
        player.forward();
        ASSERT_EQ(pos_3_2, player.getPosition());
        ASSERT_EQ(east, player.getOrientation());
    }
    TEST_F(PlayerTest, player_forward_west_test_move_in_x_axis_using_modulo) {
        Player::Orientation orientation = west;
        Player player(client.getSession(), size, pos_0_0, orientation);
        player.forward();
        ASSERT_EQ(Point(size.width - 1, 0), player.getPosition());
        ASSERT_EQ(orientation, player.getOrientation());
    }

    TEST_F(PlayerTest, player_forward_west_test_move_in_x_axis) {
        Player::Orientation orientation = west;
        Player player(client.getSession(), size, pos_2_2, orientation);
        player.forward();
        ASSERT_EQ(Point(1, 2), player.getPosition());
        ASSERT_EQ(orientation, player.getOrientation());
    }
}