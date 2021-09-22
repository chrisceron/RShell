#include "gtest/gtest.h"
#include "../header/Executable.h"
#include <string.h>
#include <stdio.h>

TEST(ExecTest, hello) {
    char str[] = "echo hello";
    //strtok(str, "\n");

    Executable* exec = new Executable(str);
    exec->execute();
    EXPECT_EQ(true, exec->execPassed);
}

TEST(ExecTest2, Quotes) {
    char str[] = "echo \"hello world\"";
    //strtok(str, "\n");

    Executable* exec = new Executable(str);
    exec->execute();
    EXPECT_EQ(true, exec->execPassed);
}


TEST(ExecTest3, helloworld) {
    char str[] = "echo hello world";
    //strtok(str, "\n");

    Executable* exec = new Executable(str);
    exec->execute();
    EXPECT_EQ(true, exec->execPassed);
}

TEST(ExecTest4, lsss) {
    char str[] = "lsss";
    //strtok(str, "\n");

    Executable* exec = new Executable(str);
    exec->execute();
    EXPECT_EQ(false, exec->execPassed);
}

TEST(ExecTest5, lsssl) {
    char str[] = "lsss -l";
    //strtok(str, "\n");

    Executable* exec = new Executable(str);
    exec->execute();
    EXPECT_EQ(false, exec->execPassed);
}
