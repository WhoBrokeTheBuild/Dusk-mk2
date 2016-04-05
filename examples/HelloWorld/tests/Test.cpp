#include <gtest/gtest.h>
#include "Test.hpp"

TEST(HelloWorld, TestFunc) {
    ASSERT_EQ(TestFunc(), 4);
}
