#include <iostream>
#include <cstdlib>
#include <climits>
using namespace std;

int maxSubArraySumN3(int arr[], int n) {
    int maxSum = INT_MIN;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int currentSum = 0;
            for (int k = i; k <= j; k++) {
                currentSum += arr[k];
            }
            maxSum = max(maxSum, currentSum);
        }
    }
    return maxSum;
}
