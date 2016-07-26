//
// Created by armanddu on 11/07/16.
//

#include <gtest/gtest.h>
#include "../../main/parser/Parser.h"

class ParserTest : public ::testing::Test {

};


TEST_F(ParserTest, parser_with_0_parameters) {
    zappy::Parser p(0, NULL);
    ASSERT_FALSE(p.isValid());
    ASSERT_EQ(p.getDeltaTime(), 100);
    ASSERT_EQ(p.getPort(), "");
    ASSERT_EQ(p.getSpectatorPort(), "");
    ASSERT_EQ(p.getTeamCount(), 0);
}

TEST_F(ParserTest, parser_with_1_parameters) {
    char *av[] = {"/"};
    zappy::Parser p(1, av);
    ASSERT_FALSE(p.isValid());
    ASSERT_EQ(p.getDeltaTime(), 100);
    ASSERT_EQ(p.getPort(), "");
    ASSERT_EQ(p.getSpectatorPort(), "");
    ASSERT_EQ(p.getTeamCount(), 0);
}

TEST_F(ParserTest, parser_with_path_and_port_parameters) {
    char *av[] = { "/", "-p", "1234" };
    zappy::Parser p(3, av);
    ASSERT_FALSE(p.isValid());
    ASSERT_EQ(p.getDeltaTime(), 100);
    ASSERT_EQ(p.getPort(), "1234");
    ASSERT_EQ(p.getSpectatorPort(), "");
    ASSERT_EQ(p.getTeamCount(), 0);
}
