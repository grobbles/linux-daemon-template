
#include <ExampleModule.hpp>
#include <gtest/gtest.h>
#include <vector>

using namespace std;

TEST(ExampleModule, test_example) {
    ExampleModule module;

    EXPECT_EQ(4, module.add(2, 2));
}