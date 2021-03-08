#include "exercises.h"
#include <tuple>

std::tuple<int,int,int> findMax(int A[], int low, int mid, int high){
    int left = INT8_MIN,right = INT8_MIN,maxleft,maxright;
    int sum = 0;

    for (int i = mid; i >= low; i--){
        sum += A[i];
        if (sum > left){
            left = sum;
            maxleft = i;
        }
    }
    sum = 0;
    for (int i = mid+1; i <= high; i++){
        sum += A[i];
        if (sum > right){
            right = sum;
            maxright = i;
        }
    }
    return std::make_tuple(maxleft,maxright, left + right);
}
std::tuple<int,int,int> maxSubsequenceDCaux(int A[], int n, int i, int j){
    std::tuple<int,int,int> left,right,middle;
    if (i == j) return std::make_tuple(i,j,A[i]);

    int mid = (i+j)/2;
    left = maxSubsequenceDCaux(A,n,i,mid);
    right = maxSubsequenceDCaux(A,n,mid+1,j);
    middle = findMax(A,i,mid,j);

    if ((std::get<2>(left) >= std::get<2>(right)) && (std::get<2>(left)>= std::get<2>(middle)) )return left;

    if ((std::get<2>(left) <= std::get<0>(right)) && (std::get<2>(right)>= std::get<2>(middle))) return right;

    return middle;

}
int maxSubsequenceDC(int A[], unsigned int n, int &i, int &j){

    std::tuple<int,int,int> res;
    i = 0, j = n-1;
    res = maxSubsequenceDCaux(A,n,i,j);
    i = std::get<0>(res);
    j = std::get<1>(res);

    return std::get<2>(res);

}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex2, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    int i, j;
   EXPECT_EQ(maxSubsequenceDC(A1,n1,i,j), 10);
   EXPECT_EQ(i, 0);
   EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDC(A2,n2,i,j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
     EXPECT_EQ(maxSubsequenceDC(A3,n3,i,j), 8);
     //EXPECT_EQ(i, 0);
    //EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDC(A4,n4,i,j), 6);
    //EXPECT_EQ(i, 3);
    //EXPECT_EQ(j, 6);
}