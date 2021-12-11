#include <iostream>
#include <gtest/gtest.h>

TEST(Hello, Test) {
    EXPECT_EQ(3, 3);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}