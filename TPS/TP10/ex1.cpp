#include "exercises.h"

#include <vector>
#include <iostream>
#include <fstream>


void computePrefixFunction(std::string pattern, int* pi){
  int m = pattern.size();
  int k = -1;

  pi[0] = -1;

  for (int q = 1; q < m; q++){
    while(k >= 0 and pattern[k+1] != pattern[q])
      k = pi[k];

    if (pattern[k+1] == pattern[q])
      k++;

    pi[q] = k;
  }
}

int kmpMatcher(std::string text, std::string pattern) {
  int n = text.size();
  int m = pattern.size();
  int q = -1;
  int match = 0;

  int pi[m];
  computePrefixFunction(pattern, pi);

  for (int i = 0; i < n; ++i){
    while(q > 0 and pattern[q+1] != text[i])
      q  =  pi[q];

    if (pattern[q + 1] == text[i])
      q++;

    if (q == m - 1){
      match ++;
      q = pi[q];
    }
  }
  return match;
}

int numStringMatching(std::string filename, std::string toSearch) {
  std::ifstream reader(filename);
  std::string sentence;
  int total = 0;

  if (!reader)
    std::cout<< "Error reading file\n";
  while(std::getline(reader,sentence)){
    total += kmpMatcher(sentence,toSearch);
  }

  return total;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP10_Ex1, testKmpMatcher) {
    EXPECT_EQ(3, kmpMatcher("aaabaabaacaabaa", "aabaa"));

    EXPECT_EQ(0, kmpMatcher("", "a"));
    EXPECT_EQ(1, kmpMatcher("a", "a"));
}

#define REL_PATH std::string("../TP10/") // relative path to the tests

TEST(TP10_Ex1, testNumStringMatching) {
    int num1 = numStringMatching(REL_PATH + "text1.txt", "estrutura de dados");
    EXPECT_EQ(3, num1);

    int num2=numStringMatching(REL_PATH +"text2.txt", "estrutura de dados");
    EXPECT_EQ(2,num2);
}
