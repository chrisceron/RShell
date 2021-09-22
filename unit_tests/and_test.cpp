#include "gtest/gtest.h"
#include "../header/Executable.h"
#include <string.h>
#include <stdio.h>
#include "../header/And.h"


TEST(AndTest, AndBothTrue) {
    char str1[] = "echo hello";
    //strtok(str1, "\n");
    char str2[] = "ls";
    //strtok(str2,"\n");


    Executable* exec1 = new Executable(str1);
    Executable* exec2 = new Executable(str2);
    Command* test1 = new And(exec1,exec2);
    test1->execute();
    EXPECT_EQ(true, test1->execPassed);
}


TEST(AndTest2, AndBothTrue2) {
    char str1[] = "ls -l";
    //strtok(str1, "\n");
    char str2[] = "pwd";
    //strtok(str2,"\n");


    Executable* exec1 = new Executable(str1);
    Executable* exec2 = new Executable(str2);
    Command* test1 = new And(exec1,exec2);
    test1->execute();
    EXPECT_EQ(true, test1->getExecPassed());
}

TEST(AndTest3, FirstTrue) {
    char str1[] = "echo hello";
    //strtok(str1, "\n");
    char str2[] = "ech";
    //strtok(str2,"\n");


    Executable* exec1 = new Executable(str1);
    Executable* exec2 = new Executable(str2);
    Command* test1 = new And(exec1,exec2);
    test1->execute();
    EXPECT_EQ(false, test1->getExecPassed());
}

TEST(AndTest4, FirstFalse) {
    char str1[] = "ech";
    //strtok(str1, "\n");
    char str2[] = "pwd";
    //strtok(str2,"\n");


    Executable* exec1 = new Executable(str1);
    Executable* exec2 = new Executable(str2);
    Command* test1 = new And(exec1,exec2);
    test1->execute();
    EXPECT_EQ(false, test1->getExecPassed());
}
