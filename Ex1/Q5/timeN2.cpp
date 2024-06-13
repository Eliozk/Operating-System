#include <iostream>
#include <cstdlib>
#include <climits>
using namespace std;

/**
 * Finds the maximum subarray sum using the brute force approach.
 * 
 * @param arr[] The input array.
 * @param n The size of the array.
 * @return The maximum subarray sum.
 */
int maxSubArraySumN2(int arr[], int n) {
    int maxSum = INT_MIN; // Initialize maxSum with the minimum possible integer value
    for (int i = 0; i < n; i++) {
        int currentSum = 0;
        for (int j = i; j < n; j++) {
            currentSum += arr[j]; // Add each element to the current sum
            maxSum = max(maxSum, currentSum); // Update maxSum if currentSum is greater
        }
    }
    return maxSum; // Return the maximum subarray sum
}
