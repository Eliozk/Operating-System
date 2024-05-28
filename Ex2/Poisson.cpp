#include <iostream>
#include <cmath> // For math functions
using namespace std;

extern "C" long double factorial(int num) {
    if (num == 0) {
        return 1;
    }
    long double res = 1;
    for (int i = num; i >= 1; i--) {
        res *= i;
    }
    return res;
}

extern "C" long double poissonCalc(long double lambda, int k) {
    return (powl(lambda, k) / factorial(k)) * expf(-lambda);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Error\n";
        return 1;
    }

    long double lambda = stold(argv[1]);
    int k = stoi(argv[2]);

    long double probability = poissonCalc(lambda, k);
    cout.precision(17);
    cout <<"Px(k) = " << probability << endl;

    return 0;
}
