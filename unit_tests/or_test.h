#include "gtest/gtest.h"
#include "../header/Executable.h"
#include "../header/Or.h"
#include <string.h>
#include <stdio.h>

TEST(OrTest, LeftTrue) {
    char str1[] = "echo hello";
    /* strtok(str1, "\n"); */
    char str2[] = "ls";
    /* strtok(str2, "\n"); */

    Executable* exec1 = new Executable(str1);
    Executable* exec2 = new Executable(str2);
    Command* test1 = new Or(exec1, exec2);
    test1->execute();
    EXPECT_EQ(true, test1->getExecPassed());
}

TEST(OrTest2, RightTrue) {
    char str1[] = "ech";
    //strtok(str1, "\n");
    char str2[] = "echo world";
    //strtok(str2, "\n");

    Executable* exec1 = new Executable(str1);
    Executable* exec2 = new Executable(str2);
    Command* test1 = new Or(exec1, exec2);
    test1->execute();
    EXPECT_EQ(true, test1->getExecPassed());
}

TEST(OrTest3, NoneTrue) {
    char str1[] = "ech";
    //strtok(str1, "\n");
    char str2[] = "lsss";
    //strtok(str2, "\n");

    Executable* exec1 = new Executable(str1);
    Executable* exec2 = new Executable(str2);
    Command* test1 = new Or(exec1, exec2);
    test1->execute();
    EXPECT_EQ(false, test1->getExecPassed());
}
