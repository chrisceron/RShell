#include "gtest/gtest.h"
#include "../header/Executable.h"
#include "../header/Test.h"

TEST(LiteralTest, NoArgument) {
    Command* executor = new Executable("test rshell");
    Command* executor2 = new Executable("test fake.txt");
    executor->execute();
    executor2->execute();

    EXPECT_EQ(true, executor->getExecPassed());
    EXPECT_EQ(false, executor2->getExecPassed());
}

TEST(LiteralTest2, eArgument) {
    Command* executor = new Executable("test -e unit_tests");
    Command* executor2 = new Executable("test -e fake_news.txt");
    executor->execute();
    executor2->execute();

    EXPECT_EQ(true, executor->getExecPassed());
    EXPECT_EQ(false, executor2->getExecPassed());
}


TEST(LiteralTest3, fArgument) {
    Command* executor = new Executable("test -f CMakeLists.txt");
    Command* executor2 = new Executable("test -f secret_agenda.txt");
    executor->execute();
    executor2->execute();

    EXPECT_EQ(true, executor->getExecPassed());
    EXPECT_EQ(false, executor2->getExecPassed());
}


TEST(LiteralTest4, dArgument) {
    Command* executor = new Executable("test -d integration_tests");
    Command* executor2 = new Executable("test -d folder");
    executor->execute();
    executor2->execute();

    EXPECT_EQ(true, executor->getExecPassed());
    EXPECT_EQ(false, executor2->getExecPassed());
}
