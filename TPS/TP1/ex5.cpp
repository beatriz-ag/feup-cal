// By: Gonçalo Leão

#include "exercises.h"

unsigned int sumArray(unsigned int a[], unsigned int n) {
    unsigned int sum = 0;
    for(unsigned int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

bool Greedy(unsigned int C[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    int i = n;
    int x = 0;
    while(i >= 0 && T >=0)
    {

        if( (C[i] > T) ) i--;
        else
        {
            usedCoins[x] = C[i];
            x++;
            T -= C[i];
        }

    }
    if (T == 0)
        return true;
    return false;
}


bool BruteForce(unsigned int C[], unsigned int n, unsigned int T, unsigned int usedCoins[]){

    int sum = 0;
    int ix = 0;
    int nrCoins = 1;
    for(int i = 0; i < n; i++)
    {
        while ((sum + C[i])< T)
        {
            sum += C[i];
            usedCoins[ix] = C[i];
            ix++;
        }
    }
    return true;

}
bool isCanonical(unsigned int C[], unsigned int n) {
    int inf = C[3] + 1;
    int sup = C[n-1] + C[n-2];
    for(int i = inf; i <= sup; i++)
    {

    }

    return false;
}
/*

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex5, canonicalTrue) {
    unsigned int C[] = {1,2,5};
    EXPECT_EQ(isCanonical(C,3), true);

    unsigned int C2[] = {1,2,5,10};
    EXPECT_EQ(isCanonical(C2,4), true);
}

TEST(TP1_Ex5, canonicalFalse) {
    unsigned int C[] = {1,4,5};
    EXPECT_EQ(isCanonical(C,3), true);
}
 */