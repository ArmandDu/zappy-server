//
// Created by armanddu on 11/07/16.
//

#include <gtest/gtest.h>
#include "../../main/world/Rect.h"

namespace zappy {
    class RectTest : public ::testing::Test {

    };

    TEST_F(RectTest, default_constructor_0_values_test) {
        Rect r;
        ASSERT_EQ(r.width, 0);
        ASSERT_EQ(r.height, 0);
        ASSERT_EQ(r.x, 0);
        ASSERT_EQ(r.y, 0);
    }

    TEST_F(RectTest, default_constructor_set_values_test) {
        Rect r(10,-10,5,-5);
        ASSERT_EQ(r.width, 10);
        ASSERT_EQ(r.height, -10);
        ASSERT_EQ(r.x, 5);
        ASSERT_EQ(r.y, -5);
    }
}
