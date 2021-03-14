#include "exercises.h"

std::string calcSum(int sequence[], unsigned long n) {
    std::string hardcoreInterpretation = "";
    int dynamicSequence[n];
    std::fill(dynamicSequence,dynamicSequence+n,0);

    int index;

    for(int m = 0; m <n; m++){
      int minValue = INT8_MAX;
      for(int i = 0; i < n-m; i++){
        dynamicSequence[i] += sequence[i+m];
        if (minValue> dynamicSequence[i]){
          minValue = dynamicSequence[i];
          index = i;
        }
      }
      hardcoreInterpretation += std::to_string(minValue) + "," +
                                std::to_string(index) + ";";
    }
    return hardcoreInterpretation;
}

void testPerformanceCalcSum() {
    //TODO
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex4, CalcSumArrayTest) {
    int sequence[5] = {4,7,2,8,1};
    int sequence2[9] = {6,1,10,3,2,6,7,2,4};

    EXPECT_EQ("1,4;9,1;11,2;18,1;22,0;",calcSum(sequence, 5));
    EXPECT_EQ("1,1;5,3;11,3;16,1;20,3;24,3;31,1;35,1;41,0;",calcSum(sequence2, 9));

	testPerformanceCalcSum();
}
