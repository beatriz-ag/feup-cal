
#include "exercises.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>


bool changeMakingUnlimitedDP(unsigned int C[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    unsigned int lastUsed[T+1];
    unsigned int change[T+1];
    std::fill(change,change+T+1,INT8_MAX);
    std::fill(usedCoins,usedCoins+n,0);

    for (int iCoin = 0; iCoin < n; iCoin++){ //Run Coins vector

        //Finding the optimal change for every change in range 0-T
        //Dynamic programming will make program effecient by storing change for smaller numbers
        //eg.  A change of 13 with 1,3,5 coins: we use the highest coin 5 and then add the change of 8 (already stored)
        for (int iPos = C[iCoin]; iPos <= T; iPos++){

            int coinsNeeded = iPos/C[iCoin];
            int rest = iPos%C[iCoin];

            if ((rest == 0) && (coinsNeeded<change[iPos])){

                change[iPos] = coinsNeeded;
                lastUsed[iPos] = C[iCoin];
            }
            else{
                int coinsTotal = coinsNeeded + change[rest];

                if (coinsTotal < change[iPos]){
                    change[iPos] = coinsTotal;
                    lastUsed[iPos] = C[iCoin];
                }
            }
        }
    }

    //TODO: think of a more effecient way to do this
   int  maxiT = T;
    while(maxiT--> 0 && T!= 0 ){
        for (int j = 0; j < n; j++){
            if (lastUsed[T] == C[j]){
                usedCoins[j]++;
                T -=  lastUsed[T];
                break;
            }
        }
    }

    return T == 0;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex2, hasChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 1);
    EXPECT_EQ(usedCoins[3], 3);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);


}

TEST(TP4_Ex2, hasChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);
}

TEST(TP4_Ex2, hasNoChange) {
    unsigned int C[] = {5,10};
    unsigned int n = 2;
    unsigned int usedCoins[2];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,1,usedCoins), false);
}