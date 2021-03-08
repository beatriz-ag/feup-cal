// By: Gonçalo Leão

#include "exercises.h"

int maxSubsequence(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    //TODO...

    int maxSum = 0;

    for (int ix = 0; ix<9; ix++)
    {
        for(int jx = 0; jx<9; jx++)
        {
            int SubSum=0;
            for(int k = ix; k <=jx;k++)
            {
                SubSum += A[k];
                if(SubSum > maxSum)
                {
                    maxSum = SubSum;
                    i = ix;
                    j = jx;
                }
            }
        }
    }

    return maxSum;
}

/*
/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex2, maxSubsequence) {
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n = 9;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequence(A,n,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}
 */