#include "exercises.h"

unsigned long s_recursive(unsigned int n, unsigned int k) {
  if (k == 1 || k == n)
    return 1;

  return s_recursive(n - 1, k - 1) + k * s_recursive(n - 1, k);
}

//THIS IS NOT RECURSIVE BUT I COULD FIGURE OUT AN ALGORITHM
//TODO THINK THINK THINK
unsigned long b_recursive(unsigned int n) {
  unsigned long res = 0;
  for (int k = 1; k <= n; k++) {
    res += s_recursive(n,k);
  }
  return res;
}
unsigned long s_dynamic(unsigned int n, unsigned int k) {
  unsigned int storage[n - k + 1];
  std::fill(storage,storage + (n-k+2),1);

  for (int i = 2 ; i <= k ; ++i) {
    for (int j = 1; j < n-k+1; ++j) {
      storage[j] += i*storage[j-1];
    }

  }
  return storage[n-k];
}

unsigned long b_dynamic(unsigned int n) {
  unsigned int storage[n + 1];

  for (int i = 1; i <= n; ++i) {
    storage[i] = 1;
    for (int k = i - 1; k > 1; --k) {
      storage[k] = storage[k - 1] + k * storage[k];
    }
  }

  int res = 0;
  for (int i = 1; i <= n; ++i) {
    res += storage[i];
  }
  return res;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex5, testPartitioningRecursive) {
  EXPECT_EQ(1, s_recursive(3, 3));
  EXPECT_EQ(3025, s_recursive(9, 3));
  EXPECT_EQ(22827, s_recursive(10, 6));

  EXPECT_EQ(5, b_recursive(3));
  EXPECT_EQ(203, b_recursive(6));
  EXPECT_EQ(1382958545, b_recursive(15));
}

TEST(TP4_Ex5, testPartitioningDynamic) {
  EXPECT_EQ(1, s_dynamic(3, 3));
  EXPECT_EQ(3025, s_dynamic(9, 3));
  EXPECT_EQ(22827, s_dynamic(10, 6));

  EXPECT_EQ(5, b_dynamic(3));
  EXPECT_EQ(203, b_dynamic(6));
  EXPECT_EQ(1382958545, b_dynamic(15));
}
