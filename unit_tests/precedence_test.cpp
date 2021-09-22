#include "gtest/gtest.h"
#include "../header/Executable.h"
#include "../header/Test.h"

TEST(PrecedenceTest, OrMiddle) {
    Command* executor = new Executable("(echo A && echo B) || (echo C && echo D)");
    Command* executor2 = new Executable("echo A && (echo B || echo c) && echo D");
    executor->execute();
    executor2->execute();

    EXPECT_EQ(true, executor->getExecPassed());
    EXPECT_EQ(true, executor2->getExecPassed());
}
