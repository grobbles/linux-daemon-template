
// #include "Observer.hpp"
#include "gtest/gtest.h"
#include <ExampleModule.hpp>
#include <vector>

using namespace std;

TEST(LogMessageSorterTest, sorted_messages) {
    ExampleModule module;

    EXPECT_EQ(4, module.add(2, 2));
}