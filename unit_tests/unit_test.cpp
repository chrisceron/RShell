#include "gtest/gtest.h"
//#include "exec_test.h"
//#include "and_test.cpp"
//#include "or_test.h"
//#include "semicolon_test.cpp"

#include "test_literal.cpp"
#include "test_symbolic.cpp"
//#include "precedence_test.cpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
