#include <iostream>
#include <cstdlib>
#include <climits>
using namespace std;

int maxSubArraySumN(int arr[], int n) {
    int max_so_far = arr[0];
    int curr_max = arr[0];

    for (int i = 1; i < n; i++) {
        curr_max = max(arr[i], curr_max + arr[i]);//calc arr[i]+curr if bigger choose it else arr[i]
        max_so_far = max(max_so_far, curr_max);
    }

    return max_so_far;
}
