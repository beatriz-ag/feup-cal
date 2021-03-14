#include "exercises.h"

int maxSubsequenceDP(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
  int dynamicSequence[n]; //Array to be register previous sums

  int index[n]; //Array to keep track of indexes (e.g: index[0] = starting
                // index of subArray with 1 element
  int maxSumM[n]; //Array to keep track of the sum corresponding to a group
                  // of n elements maxSumM[0] = max sum with 1 element
                  // maxSumM[1] = max sum of 2 continuous elements and so on
  std::fill(dynamicSequence,dynamicSequence+n,0);
  std::fill(maxSumM,maxSumM+n,INT8_MIN);

  for(int m = 0; m <n; m++){
    for(int i = 0; i < n-m; i++){
      dynamicSequence[i] += A[i+m];
      if (maxSumM[m]< dynamicSequence[i]){
        maxSumM[m] = dynamicSequence[i];
        index[m] = i;
      }
    }
  }

  //Search max subarray
  int maxIndex = 0, maxSum = maxSumM[0];
  for(int i = 0; i <n; i++){
    if (maxSumM[i] > maxSum){
      maxIndex = i;
      maxSum = maxSumM[i];
    }
  }
  i = index[maxIndex];
  j = i+maxIndex;
  return maxSum;
}
void testPerformanceMaxSubsequence() {
	// TODO
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex6, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequenceDP(A1,n1,i,j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDP(A2,n2,i,j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDP(A3,n3,i,j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDP(A4,n4,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);

    testPerformanceMaxSubsequence();
}
