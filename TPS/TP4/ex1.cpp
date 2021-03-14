#include "exercises.h"
#include <vector>
unsigned long factorialRecurs(unsigned long n) {
    if (n == 0 || n == 1) return 1;

    return  n * factorialRecurs(n-1);
}

unsigned int mem[INT8_MAX] = {};

unsigned long factorialDP(unsigned long n) {

    if (mem[n] != NULL) return n;
    if (n == 0 || n == 1){
        mem[0] = 1;
        mem[1] = 1;
        return 1;
    }
    unsigned int factorial = n * factorialDP(n-1);

    mem[n] = factorial;

    return  n * factorialRecurs(n-1);
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex1, FactorialTest) {
    EXPECT_EQ(1,factorialRecurs(0));
    EXPECT_EQ(1,factorialRecurs(1));
    EXPECT_EQ(2,factorialRecurs(2));
    EXPECT_EQ(6,factorialRecurs(3));
    EXPECT_EQ(24,factorialRecurs(4));
    EXPECT_EQ(120,factorialRecurs(5));
    EXPECT_EQ(3628800,factorialRecurs(10));
    EXPECT_EQ(1,factorialDP(0));
    EXPECT_EQ(1,factorialDP(1));
    EXPECT_EQ(2,factorialDP(2));
    EXPECT_EQ(6,factorialDP(3));
    EXPECT_EQ(24,factorialDP(4));
    EXPECT_EQ(120,factorialDP(5));
    EXPECT_EQ(3628800,factorialDP(10));
}