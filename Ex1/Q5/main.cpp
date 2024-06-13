/**
 * @file main.cpp
 * @brief Program to compare three algorithms for finding the maximum subarray sum.
 * 
 * This program generates an array of random integers, then runs three different algorithms
 * to find the maximum subarray sum. It compares the execution times of these algorithms and
 * also measures the time taken for random number generation.
 */

#include <iostream>
#include <cstdlib>
#include <chrono>
using namespace std;

/**
 * @brief Prints the elements of an array.
 * @param arr The array to be printed.
 * @param size The size of the array.
 */
void printarr(int arr[], int size) {
    cout << "The Array: ";
    cout << "{";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i != size - 1) {
            cout << ", ";
        }
    }
    cout << "}\n";
}

// Function prototypes
int maxSubArraySumN(int arr[], int n);
int maxSubArraySumN2(int arr[], int n);
int maxSubArraySumN3(int arr[], int n);

int main() {
    int seed, n;

    cout << "Enter random seed: ";//same seed will give same random array help in check of running time
    cin >> seed;

    cout << "Enter size of the array: ";
    cin >> n;
    cout << "\n";

    auto startRand = chrono::high_resolution_clock::now(); // Start timer for random number generation

    int *arr = new int[n];
    srand(seed);

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 101 - 25; // random between [-25, 75]
    }

    auto endRand = chrono::high_resolution_clock::now(); // End timer for random number generation
    chrono::duration<double> elapsedRand = endRand - startRand; // Calculate elapsed time

    printarr(arr, n);

    auto start = chrono::high_resolution_clock::now();
    int maxSum;

    // Run first algorithm (O(n))
    maxSum = maxSubArraySumN(arr, n);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "\nMax subarray sum (O(n)): " << maxSum << endl;
    cout << "Time taken for algorithm: " << elapsed.count() << " seconds" << endl;
    cout << "Time taken for random number generation: " << elapsedRand.count() << " seconds" << endl;

    // Run second algorithm (O(n^2))
    start = chrono::high_resolution_clock::now();
    maxSum = maxSubArraySumN2(arr, n);
    end = chrono::high_resolution_clock::now();
    elapsed = end - start;

    cout << "\nMax subarray sum (O(n^2)): " << maxSum << endl;
    cout << "Time taken for algorithm: " << elapsed.count() << " seconds" << endl;
    cout << "Time taken for random number generation: " << elapsedRand.count() << " seconds" << endl;

    // Run third algorithm (O(n^3))
    start = chrono::high_resolution_clock::now();
    maxSum = maxSubArraySumN3(arr, n);
    end = chrono::high_resolution_clock::now();
    elapsed = end - start;

    cout << "\nMax subarray sum (O(n^3)): " << maxSum << endl;
    cout << "Time taken for algorithm: " << elapsed.count() << " seconds" << endl;
    cout << "Time taken for random number generation: " << elapsedRand.count() << " seconds" << endl;

    delete[] arr;
    return 0;
}
