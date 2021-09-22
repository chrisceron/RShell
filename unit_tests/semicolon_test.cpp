#include "gtest/gtest.h"
#include "../header/Executable.h"
#include <string.h>
#include <stdio.h>
#include "../header/Semicolon.h"


TEST(SemicolonTest, SemiBothTrue) {
    char str1[] = "echo hello";
    //strtok(str1, "\n");
    char str2[] = "ls";
    //strtok(str2,"\n");


    Executable* exec1 = new Executable(str1);
    Executable* exec2 = new Executable(str2);
    Command* test1 = new Semicolon(exec1,exec2);
    test1->execute();
    EXPECT_EQ(true, test1->getExecPassed());
}


TEST(SemicolonTest2, SemiBothTrue2) {
    char str1[] = "ls";
    //strtok(str1, "\n");
    char str2[] = "pwd";
    //strtok(str2,"\n");


    Executable* exec1 = new Executable(str1);
    Executable* exec2 = new Executable(str2);
    Command* test1 = new Semicolon(exec1,exec2);
    test1->execute();
    EXPECT_EQ(true, test1->getExecPassed());
}

TEST(SemicolonTest3, LeftTrue) {
    char str1[] = "ls";
    //strtok(str1, "\n");
    char str2[] = "ech -l";
    //strtok(str2,"\n");


    Executable* exec1 = new Executable(str1);
    Executable* exec2 = new Executable(str2);
    Command* test1 = new Semicolon(exec1,exec2);
    test1->execute();
    EXPECT_EQ(false, test1->getExecPassed());
}

TEST(SemicolonTest4, RightTrue) {
    char str1[] = "lsss";
    //strtok(str1, "\n");
    char str2[] = "pwd";
    //strtok(str2,"\n");


    Executable* exec1 = new Executable(str1);
    Executable* exec2 = new Executable(str2);
    Command* test1 = new Semicolon(exec1,exec2);
    test1->execute();
    EXPECT_EQ(true, test1->getExecPassed());
}


TEST(SemicolonTest5, NoneTrue) {
    char str1[] = "lsss";
    //strtok(str1, "\n");
    char str2[] = "ech";
    //strtok(str2,"\n");


    Executable* exec1 = new Executable(str1);
    Executable* exec2 = new Executable(str2);
    Command* test1 = new Semicolon(exec1,exec2);
    test1->execute();
    EXPECT_EQ(false, test1->getExecPassed());
}
