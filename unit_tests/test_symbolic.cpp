#include "gtest/gtest.h"
#include "../header/Executable.h"
#include "../header/Test.h"

TEST(SymbolicTest, NoArgument) {
    Command* executor = new Executable("[ unit_tests ]");
    Command* executor2 = new Executable("[ fake_news.txt ]");
    executor->execute();
    executor2->execute();

    EXPECT_EQ(true, executor->getExecPassed());
    EXPECT_EQ(false, executor2->getExecPassed());
}

TEST(SymbolicTest2, eArgument) {
    Command* executor = new Executable("[ -e CMakeLists.txt ]");
    Command* executor2 = new Executable("[ -e fakefile ]");
    executor->execute();
    executor2->execute();

    EXPECT_EQ(true, executor->getExecPassed());
    EXPECT_EQ(false, executor2->getExecPassed());
}

TEST(SymbolicTest3, fArgument) {
    Command* executor = new Executable("[ -f rshell ]");
    Command* executor2 = new Executable("[ -f secret_recipe.txt ]");
    executor->execute();
    executor2->execute();

    EXPECT_EQ(true, executor->getExecPassed());
    EXPECT_EQ(false, executor2->getExecPassed());
}

TEST(SymbolicTest4, dArgument) {
    Command* executor = new Executable("[ -d header ]");
    Command* executor2 = new Executable("[ -d nonexecutable ]");
    executor->execute();
    executor2->execute();

    EXPECT_EQ(true, executor->getExecPassed());
    EXPECT_EQ(false, executor2->getExecPassed());
}
