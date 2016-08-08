//
// Created by armanddu on 22/07/16.
//

#include <gtest/gtest.h>
#include "../../../main/world/actors/player/actions/IncantationAction.h"

namespace zappy {
    class IncantationTest : public ::testing::Test {

    protected:
        double duration = Player::Command::Duration::Incantation * 10000; //1ms = 300 * 10 zappy seconds => 0.001ms = 300 zappy second <=> incantationDuration

    };


    TEST_F(IncantationTest, test_initial_values_of_player) {
        Game game = Game(0, Rect(1, 1, 0, 0), std::vector<std::string>(), 1);
        my_tcp::Client client;
        Player player = Player(client.getSession(), game.getWorld().getSize(), Point(), Player::Orientation::East);
        ASSERT_EQ(player.getLevel(), 1);
        ASSERT_FALSE(player.isIncanting());
    }

    TEST_F(IncantationTest, test_incantation_with_more_than_enough_requirement_pass_level_2) {
        IncantationAction action;
        Game game = Game(0, Rect(1, 1, 0, 0), std::vector<std::string>(), 1);
        game.getWorld().generateResources<World::Fertility::Abundant>();
        int nPlayers = 1;
        int level_start = 1;
        int level_end = 2;

        for (int i = 0; i < nPlayers; ++i) {
            my_tcp::Client client;
            Player player = Player(client.getSession(), game.getWorld().getSize(), Point(), Player::Orientation::East);
            game.addPlayer(player);
        }
        while (game.getPlayers().back().getLevel() < level_start) {
            std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [](Player &p){return p.levelUp();});
        }

        action.trigger(game.getPlayers().front(), "", "", game);
        std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [this, level_start, level_end](Player &player) {
            ASSERT_EQ(player.getLevel(), level_start);
            while (player.isBusy()) player.updateCmdTimeout(duration);
            ASSERT_EQ(player.getLevel(), level_end);
        });
    }

    TEST_F(IncantationTest, test_incantation_with_more_than_enough_players_pass_level_2) {
        IncantationAction action;
        Game game = Game(0, Rect(1, 1, 0, 0), std::vector<std::string>(), 1);
        game.getWorld().generateResources<World::Fertility::Abundant>();
        int nPlayers = 9;
        int level_start = 1;
        int level_end = 2;

        for (int i = 0; i < nPlayers; ++i) {
            my_tcp::Client client;
            Player player = Player(client.getSession(), game.getWorld().getSize(), Point(), Player::Orientation::East);
            game.addPlayer(player);
        }
        while (game.getPlayers().back().getLevel() < level_start) {
            std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [](Player &p){return p.levelUp();});
        }

        action.trigger(game.getPlayers().front(), "", "", game);
        std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [this, level_start, level_end](Player &player) {
            ASSERT_EQ(player.getLevel(), level_start);
            while (player.isBusy()) player.updateCmdTimeout(duration);
            ASSERT_EQ(player.getLevel(), level_end);
        });
    }

    TEST_F(IncantationTest, test_incantation_with_more_than_enough_requirement_pass_level_3) {
        Game game = Game(0, Rect(1, 1, 0, 0), std::vector<std::string>(), 1);
        game.getWorld().generateResources<World::Fertility::Abundant>();

        IncantationAction action;
        int nPlayers = 2;
        int level_start = 2;
        int level_end = 3;

        for (int i = 0; i < nPlayers; ++i) {
            my_tcp::Client client;
            Player player = Player(client.getSession(), game.getWorld().getSize(), Point(), Player::Orientation::East);
            game.addPlayer(player);
        }
        while (game.getPlayers().back().getLevel() < level_start) {
            std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [](Player &p){return p.levelUp();});
        }

        action.trigger(game.getPlayers().front(), "", "", game);
        std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [this, level_start, level_end](Player &player) {
            ASSERT_EQ(player.getLevel(), level_start);
            while (player.isBusy()) player.updateCmdTimeout(duration);
            ASSERT_EQ(player.getLevel(), level_end);
        });
    }

    TEST_F(IncantationTest, test_incantation_with_more_than_enough_players_pass_level_3) {
        IncantationAction action;
        Game game = Game(0, Rect(1, 1, 0, 0), std::vector<std::string>(), 1);
        game.getWorld().generateResources<World::Fertility::Abundant>();
        int nPlayers = 9;
        int level_start = 2;
        int level_end = 3;

        for (int i = 0; i < nPlayers; ++i) {
            my_tcp::Client client;
            Player player = Player(client.getSession(), game.getWorld().getSize(), Point(), Player::Orientation::East);
            game.addPlayer(player);
        }
        while (game.getPlayers().back().getLevel() < level_start) {
            std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [](Player &p){return p.levelUp();});
        }

        action.trigger(game.getPlayers().front(), "", "", game);
        std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [this, level_start, level_end](Player &player) {
            ASSERT_EQ(player.getLevel(), level_start);
            while (player.isBusy())player.updateCmdTimeout(duration);
            ASSERT_EQ(player.getLevel(), level_end);
        });
    }

    TEST_F(IncantationTest, test_incantation_with_not_enough_players_do_not_pass_level_3) {
        Game game = Game(0, Rect(1, 1, 0, 0), std::vector<std::string>(), 1);
        game.getWorld().generateResources<World::Fertility::Abundant>();
        IncantationAction action;
        int nPlayers = 1;
        int level_start = 2;
        int level_end = 2;

        for (int i = 0; i < nPlayers; ++i) {
            my_tcp::Client client;
            Player player = Player(client.getSession(), game.getWorld().getSize(), Point(), Player::Orientation::East);
            game.addPlayer(player);
        }
        ASSERT_EQ(game.getPlayers().size(), nPlayers);
        while (game.getPlayers().front().getLevel() < level_start) {
            std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [](Player &p){return p.levelUp();});
        }
        action.trigger(game.getPlayers().front(), "", "", game);
        std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [this, level_start, level_end](Player &player) {
            ASSERT_EQ(player.getLevel(), level_start);
            while (player.isBusy()) player.updateCmdTimeout(duration);
            ASSERT_EQ(player.getLevel(), level_end);
        });
    }

    TEST_F(IncantationTest, test_incantation_with_more_than_enough_requirement_pass_level_4) {
        Game game = Game(0, Rect(1, 1, 0, 0), std::vector<std::string>(), 1);
        game.getWorld().generateResources<World::Fertility::Abundant>();
        IncantationAction action;
        int nPlayers = 2;
        int level_start = 3;
        int level_end = 4;

        for (int i = 0; i < nPlayers; ++i) {
            my_tcp::Client client;
            Player player = Player(client.getSession(), game.getWorld().getSize(), Point(), Player::Orientation::East);
            game.addPlayer(player);
        }
        while (game.getPlayers().back().getLevel() < level_start) {
            std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [](Player &p){return p.levelUp();});
        }

        action.trigger(game.getPlayers().front(), "", "", game);
        std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [this, level_start, level_end](Player &player) {
            ASSERT_EQ(player.getLevel(), level_start);
            while (player.isBusy()) player.updateCmdTimeout(duration);
            ASSERT_EQ(player.getLevel(), level_end);
        });
    }

    TEST_F(IncantationTest, test_incantation_with_more_than_enough_players_pass_level_4) {
        IncantationAction action;
        Game game = Game(0, Rect(1, 1, 0, 0), std::vector<std::string>(), 1);
        game.getWorld().generateResources<World::Fertility::Abundant>();
        int nPlayers = 9;
        int level_start = 3;
        int level_end = 4;

        for (int i = 0; i < nPlayers; ++i) {
            my_tcp::Client client;
            Player player = Player(client.getSession(), game.getWorld().getSize(), Point(), Player::Orientation::East);
            game.addPlayer(player);
        }
        while (game.getPlayers().back().getLevel() < level_start) {
            std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [](Player &p){return p.levelUp();});
        }

        action.trigger(game.getPlayers().front(), "", "", game);
        std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [this, level_start, level_end](Player &player) {
            ASSERT_EQ(player.getLevel(), level_start);
            while (player.isBusy()) player.updateCmdTimeout(duration);
            ASSERT_EQ(player.getLevel(), level_end);
        });
    }

    TEST_F(IncantationTest, test_incantation_with_not_enough_players_do_not_pass_level_4) {
        Game game = Game(0, Rect(1, 1, 0, 0), std::vector<std::string>(), 1);
        game.getWorld().generateResources<World::Fertility::Abundant>();
        IncantationAction action;
        int nPlayers = 1;
        int level_start = 3;
        int level_end = 3;

        for (int i = 0; i < nPlayers; ++i) {
            my_tcp::Client client;
            Player player = Player(client.getSession(), game.getWorld().getSize(), Point(), Player::Orientation::East);
            game.addPlayer(player);
        }
        while (game.getPlayers().back().getLevel() < level_start) {
            std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [](Player &p){return p.levelUp();});
        }

        action.trigger(game.getPlayers().front(), "", "", game);
        std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [this, level_start, level_end](Player &player) {
            ASSERT_EQ(player.getLevel(), level_start);
            while (player.isBusy()) player.updateCmdTimeout(duration);
            ASSERT_EQ(player.getLevel(), level_end);
        });
    }

    TEST_F(IncantationTest, test_incantation_with_more_than_enough_requirement_pass_level_5) {
        Game game = Game(0, Rect(1, 1, 0, 0), std::vector<std::string>(), 1);
        game.getWorld().generateResources<World::Fertility::Abundant>();

        IncantationAction action;
        int nPlayers = 4;
        int level_start = 4;
        int level_end = 5;

        for (int i = 0; i < nPlayers; ++i) {
            my_tcp::Client client;
            Player player = Player(client.getSession(), game.getWorld().getSize(), Point(), Player::Orientation::East);
            game.addPlayer(player);
        }
        while (game.getPlayers().back().getLevel() < level_start) {
            std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [](Player &p){return p.levelUp();});
        }

        action.trigger(game.getPlayers().front(), "", "", game);
        std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [this, level_start, level_end](Player &player) {
            ASSERT_EQ(player.getLevel(), level_start);
            while (player.isBusy()) player.updateCmdTimeout(duration);
            ASSERT_EQ(player.getLevel(), level_end);
        });
    }

    TEST_F(IncantationTest, test_incantation_with_more_than_enough_players_pass_level_5) {
        IncantationAction action;
        Game game = Game(0, Rect(1, 1, 0, 0), std::vector<std::string>(), 1);
        game.getWorld().generateResources<World::Fertility::Abundant>();
        int nPlayers = 9;
        int level_start = 4;
        int level_end = 5;

        for (int i = 0; i < nPlayers; ++i) {
            my_tcp::Client client;
            Player player = Player(client.getSession(), game.getWorld().getSize(), Point(), Player::Orientation::East);
            game.addPlayer(player);
        }
        while (game.getPlayers().back().getLevel() < level_start) {
            std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [](Player &p){return p.levelUp();});
        }

        action.trigger(game.getPlayers().front(), "", "", game);
        std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [this, level_start, level_end](Player &player) {
            ASSERT_EQ(player.getLevel(), level_start);
            while (player.isBusy()) player.updateCmdTimeout(duration);
            ASSERT_EQ(player.getLevel(), level_end);
        });
    }

    TEST_F(IncantationTest, test_incantation_with_not_enough_players_do_not_pass_level_5) {
        Game game = Game(0, Rect(1, 1, 0, 0), std::vector<std::string>(), 1);
        game.getWorld().generateResources<World::Fertility::Abundant>();

        IncantationAction action;
        int nPlayers = 1;
        int level_start = 4;
        int level_end = 4;

        for (int i = 0; i < nPlayers; ++i) {
            my_tcp::Client client;
            Player player = Player(client.getSession(), game.getWorld().getSize(), Point(), Player::Orientation::East);
            game.addPlayer(player);
        }
        while (game.getPlayers().back().getLevel() < level_start) {
            std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [](Player &p){return p.levelUp();});
        }

        action.trigger(game.getPlayers().front(), "", "", game);
        std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [this, level_start, level_end](Player &player) {
            ASSERT_EQ(player.getLevel(), level_start);
            while (player.isBusy()) player.updateCmdTimeout(duration);
            ASSERT_EQ(player.getLevel(), level_end);
        });
    }

    TEST_F(IncantationTest, test_incantation_with_more_than_enough_requirement_pass_level_6) {
        Game game = Game(0, Rect(1, 1, 0, 0), std::vector<std::string>(), 1);
        game.getWorld().generateResources<World::Fertility::Abundant>();

        IncantationAction action;
        int nPlayers = 6;
        int level_start = 5;
        int level_end = 6;

        for (int i = 0; i < nPlayers; ++i) {
            my_tcp::Client client;
            Player player = Player(client.getSession(), game.getWorld().getSize(), Point(), Player::Orientation::East);
            game.addPlayer(player);
        }
        while (game.getPlayers().back().getLevel() < level_start) {
            std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [](Player &p){return p.levelUp();});
        }

        action.trigger(game.getPlayers().front(), "", "", game);
        std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [this, level_start, level_end](Player &player) {
            ASSERT_EQ(player.getLevel(), level_start);
            while (player.isBusy()) player.updateCmdTimeout(duration);
            ASSERT_EQ(player.getLevel(), level_end);
        });
    }

    TEST_F(IncantationTest, test_incantation_with_more_than_enough_players_pass_level_6) {
        IncantationAction action;
        Game game = Game(0, Rect(1, 1, 0, 0), std::vector<std::string>(), 1);
        game.getWorld().generateResources<World::Fertility::Abundant>();
        int nPlayers = 9;
        int level_start = 5;
        int level_end = 6;

        for (int i = 0; i < nPlayers; ++i) {
            my_tcp::Client client;
            Player player = Player(client.getSession(), game.getWorld().getSize(), Point(), Player::Orientation::East);
            game.addPlayer(player);
        }
        while (game.getPlayers().back().getLevel() < level_start) {
            std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [](Player &p){return p.levelUp();});
        }

        action.trigger(game.getPlayers().front(), "", "", game);
        std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [this, level_start, level_end](Player &player) {
            ASSERT_EQ(player.getLevel(), level_start);
            while (player.isBusy()) player.updateCmdTimeout(duration);
            ASSERT_EQ(player.getLevel(), level_end);
        });
    }

    TEST_F(IncantationTest, test_incantation_with_not_enough_players_do_not_pass_level_6) {
        Game game = Game(0, Rect(1, 1, 0, 0), std::vector<std::string>(), 1);
        game.getWorld().generateResources<World::Fertility::Abundant>();
        IncantationAction action;
        int nPlayers = 1;
        int level_start = 5;
        int level_end = 5;

        for (int i = 0; i < nPlayers; ++i) {
            my_tcp::Client client;
            Player player = Player(client.getSession(), game.getWorld().getSize(), Point(), Player::Orientation::East);
            game.addPlayer(player);
        }
        while (game.getPlayers().back().getLevel() < level_start) {
            std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [](Player &p){return p.levelUp();});
        }

        action.trigger(game.getPlayers().front(), "", "", game);
        std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [this, level_start, level_end](Player &player) {
            ASSERT_EQ(player.getLevel(), level_start);
            while (player.isBusy()) player.updateCmdTimeout(duration);
            ASSERT_EQ(player.getLevel(), level_end);
        });
    }

    TEST_F(IncantationTest, test_incantation_with_more_than_enough_requirement_pass_level_7) {
        Game game = Game(0, Rect(1, 1, 0, 0), std::vector<std::string>(), 1);
        game.getWorld().generateResources<World::Fertility::Abundant>();

        IncantationAction action;
        int nPlayers = 6;
        int level_start = 6;
        int level_end = 7;

        for (int i = 0; i < nPlayers; ++i) {
            my_tcp::Client client;
            Player player = Player(client.getSession(), game.getWorld().getSize(), Point(), Player::Orientation::East);
            game.addPlayer(player);
        }
        while (game.getPlayers().back().getLevel() < level_start) {
            std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [](Player &p){return p.levelUp();});
        }

        action.trigger(game.getPlayers().front(), "", "", game);
        std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [this, level_start, level_end](Player &player) {
            ASSERT_EQ(player.getLevel(), level_start);
            while (player.isBusy()) player.updateCmdTimeout(duration);
            ASSERT_EQ(player.getLevel(), level_end);
        });
    }

    TEST_F(IncantationTest, test_incantation_with_more_than_enough_players_pass_level_7) {
        IncantationAction action;
        Game game = Game(0, Rect(1, 1, 0, 0), std::vector<std::string>(), 1);
        game.getWorld().generateResources<World::Fertility::Abundant>();
        int nPlayers = 9;
        int level_start = 6;
        int level_end = 7;

        for (int i = 0; i < nPlayers; ++i) {
            my_tcp::Client client;
            Player player = Player(client.getSession(), game.getWorld().getSize(), Point(), Player::Orientation::East);
            game.addPlayer(player);
        }
        while (game.getPlayers().back().getLevel() < level_start) {
            std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [](Player &p){return p.levelUp();});
        }

        action.trigger(game.getPlayers().front(), "", "", game);
        std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [this, level_start, level_end](Player &player) {
            ASSERT_EQ(player.getLevel(), level_start);
            while (player.isBusy()) player.updateCmdTimeout(duration);
            ASSERT_EQ(player.getLevel(), level_end);
        });
    }

    TEST_F(IncantationTest, test_incantation_with_not_enough_players_do_not_pass_level_7) {
        Game game = Game(0, Rect(1, 1, 0, 0), std::vector<std::string>(), 1);
        game.getWorld().generateResources<World::Fertility::Abundant>();

        IncantationAction action;
        int nPlayers = 1;
        int level_start = 6;
        int level_end = 6;

        for (int i = 0; i < nPlayers; ++i) {
            my_tcp::Client client;
            Player player = Player(client.getSession(), game.getWorld().getSize(), Point(), Player::Orientation::East);
            game.addPlayer(player);
        }
        while (game.getPlayers().back().getLevel() < level_start) {
            std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [](Player &p){return p.levelUp();});
        }

        action.trigger(game.getPlayers().front(), "", "", game);
        std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [this, level_start, level_end](Player &player) {
            ASSERT_EQ(player.getLevel(), level_start);
            while (player.isBusy()) player.updateCmdTimeout(duration);
            ASSERT_EQ(player.getLevel(), level_end);
        });
    }

    TEST_F(IncantationTest, test_incantation_with_more_than_enough_requirement_pass_level_8) {
        Game game = Game(0, Rect(1, 1, 0, 0), std::vector<std::string>(), 1);
        game.getWorld().generateResources<World::Fertility::Abundant>();

        IncantationAction action;
        int nPlayers = 6;
        int level_start = 7;
        int level_end = 8;

        for (int i = 0; i < nPlayers; ++i) {
            my_tcp::Client client;
            Player player = Player(client.getSession(), game.getWorld().getSize(), Point(), Player::Orientation::East);
            game.addPlayer(player);
        }
        while (game.getPlayers().back().getLevel() < level_start) {
            std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [](Player &p){return p.levelUp();});
        }

        action.trigger(game.getPlayers().front(), "", "", game);
        std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [this, level_start, level_end](Player &player) {
            ASSERT_EQ(player.getLevel(), level_start);
            while (player.isBusy()) player.updateCmdTimeout(duration);
            ASSERT_EQ(player.getLevel(), level_end);
        });
    }

    TEST_F(IncantationTest, test_incantation_with_more_than_enough_players_pass_level_8) {
        IncantationAction action;
        Game game = Game(0, Rect(1, 1, 0, 0), std::vector<std::string>(), 1);
        game.getWorld().generateResources<World::Fertility::Abundant>();
        int nPlayers = 9;
        int level_start = 7;
        int level_end = 8;

        for (int i = 0; i < nPlayers; ++i) {
            my_tcp::Client client;
            Player player = Player(client.getSession(), game.getWorld().getSize(), Point(), Player::Orientation::East);
            game.addPlayer(player);
        }
        while (game.getPlayers().back().getLevel() < level_start) {
            std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [](Player &p){return p.levelUp();});
        }

        action.trigger(game.getPlayers().front(), "", "", game);
        std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [this, level_start, level_end](Player &player) {
            ASSERT_EQ(player.getLevel(), level_start);
            while (player.isBusy()) player.updateCmdTimeout(duration);
            ASSERT_EQ(player.getLevel(), level_end);
        });
    }

    TEST_F(IncantationTest, test_incantation_with_not_enough_players_do_not_pass_level_8) {
        Game game = Game(0, Rect(1, 1, 0, 0), std::vector<std::string>(), 1);
        game.getWorld().generateResources<World::Fertility::Abundant>();

        IncantationAction action;
        int nPlayers = 1;
        int level_start = 7;
        int level_end = 7;

        for (int i = 0; i < nPlayers; ++i) {
            my_tcp::Client client;
            Player player = Player(client.getSession(), game.getWorld().getSize(), Point(), Player::Orientation::East);
            game.addPlayer(player);
        }
        while (game.getPlayers().back().getLevel() < level_start) {
            std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [](Player &p){return p.levelUp();});
        }

        action.trigger(game.getPlayers().front(), "", "", game);
        std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [this, level_start, level_end](Player &player) {
            ASSERT_EQ(player.getLevel(), level_start);
            while (player.isBusy()) player.updateCmdTimeout(duration);
            ASSERT_EQ(player.getLevel(), level_end);
        });
    }

    TEST_F(IncantationTest, test_incantation_do_not_pass_level_9) {
        Game game = Game(0, Rect(1, 1, 0, 0), std::vector<std::string>(), 1);
        game.getWorld().generateResources<World::Fertility::Abundant>();

        IncantationAction action;
        int nPlayers = 19;
        int level_start = 8;
        int level_end = 8;

        for (int i = 0; i < nPlayers; ++i) {
            my_tcp::Client client;
            Player player = Player(client.getSession(), game.getWorld().getSize(), Point(), Player::Orientation::East);
            game.addPlayer(player);
        }
        while (game.getPlayers().back().getLevel() < level_start) {
            std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [](Player &p){return p.levelUp();});
        }

        action.trigger(game.getPlayers().front(), "", "", game);
        std::for_each(game.getPlayers().begin(), game.getPlayers().end(), [this, level_start, level_end](Player &player) {
            ASSERT_EQ(player.getLevel(), level_start);
            while (player.isBusy()) player.updateCmdTimeout(duration);
            ASSERT_EQ(player.getLevel(), level_end);
        });
    }

}