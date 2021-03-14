#include "exercises.h"

bool stockConfict(unsigned int C[], unsigned int Stock[], unsigned int n,
                  unsigned int T, unsigned int usedCoins[]){
  int iCoin = n-1;
  std::fill(usedCoins, usedCoins + n, 0);
  unsigned int *stockSaver= Stock;

  while(T > 0 && iCoin >= 0){
      if(C[iCoin]> T || stockSaver[iCoin] == 0) iCoin--;
      T -= C[iCoin];
      usedCoins[iCoin]++;
    stockSaver[iCoin]--;
      if (!stockSaver[iCoin]) iCoin--;
  }
  return T == 0;
}
bool changeMakingDP(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {


    unsigned int lastUsed[T + 1];
    unsigned int change[T + 1];

    std::fill(change, change + T + 1, INT8_MAX);
    std::fill(usedCoins, usedCoins + n, 0);

    for (int iCoin = 0; iCoin < n; iCoin++) { //Run Coins vector

        //Finding the optimal change for every change in range 0-T
        //Dynamic programming will make program effecient by storing change for smaller numbers
        //eg.  A change of 13 with 1,3,5 coins: we use the highest coin 5 and then add the change of 8 (already stored)
        for (int iPos = C[iCoin]; iPos <= T; iPos++) {

            int coinsNeeded = iPos / C[iCoin];

            //STOCK
            int rest;

            if (coinsNeeded > Stock[iCoin]){
              coinsNeeded = Stock[iCoin];
              rest = iPos - (Stock[iCoin]*C[iCoin]);
            }
            else{
              rest = iPos % C[iCoin];
            }
            if ((rest == 0) && (coinsNeeded < change[iPos])) {

                change[iPos] = coinsNeeded;
                lastUsed[iPos] = C[iCoin];
            } else {
                int coinsTotal = coinsNeeded + change[rest];
                if (coinsTotal < change[iPos]) {

                    change[iPos] = coinsTotal;
                    lastUsed[iPos] = C[iCoin];
                }
            }
        }
    }

    //TODO: think of a more effecient way to do this
    int maxiT = T;
    int stockConfictT = T;
    while (maxiT-- > 0 && T != 0) {
        for (int j = 0; j < n; j++) {
            if (lastUsed[T] == C[j]) {
                usedCoins[j]++;

                if (usedCoins[j] > Stock[j])
                  return stockConfict(C,Stock,n,stockConfictT,usedCoins);

                T -= lastUsed[T];
                break;
            }
        }
    }

    return T == 0;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex3, hasChangeCanonical) {
    unsigned int C[] = {1, 2, 5, 10};
    unsigned int Stock[] = {1, 1, 1, 1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingDP(C, Stock, n, 13, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1, 2, 4, 2};
    EXPECT_EQ(changeMakingDP(C, Stock2, n, 38, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10, 2, 4, 2};
    EXPECT_EQ(changeMakingDP(C, Stock3, n, 10, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP4_Ex3, hasChangeNonCanonical) {
    unsigned int C[] = {1, 4, 5};
    unsigned int Stock[] = {2, 2, 1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingDP(C, Stock, n, 6, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingDP(C, Stock, n, 8, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8, 2, 1};
    EXPECT_EQ(changeMakingDP(C, Stock2, n, 7, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingDP(C, Stock2, n, 8, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP4_Ex3, hasNoChange) {
    unsigned int C[] = {1, 2, 5, 10};
    unsigned int Stock[] = {0, 1, 1, 1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingDP(C, Stock, n, 18, usedCoins), false);
    EXPECT_EQ(changeMakingDP(C, Stock, n, 1, usedCoins), false);
}
