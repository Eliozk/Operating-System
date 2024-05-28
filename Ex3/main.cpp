#include <iostream>
#include <dlfcn.h>
using namespace std;

// Define a function pointer type for the Poisson calculation function
typedef long double (*poissonCalc_t)(long double, int);

int main() {
    // Load the shared library containing the Poisson calculation function
    void* handle = dlopen("/home/elioz/Operating Systems/Ex2/libpoisson.so", RTLD_LAZY);
    if (!handle) {
        cerr << "Error: Cannot open library: " << dlerror() << '\n';  // Error message if library cannot be opened
        return 1;
    }

    // Load the Poisson calculation function from the shared library
    poissonCalc_t poisson = (poissonCalc_t) dlsym(handle, "poissonCalc");
    if (!poisson) {
        cerr << "Error: Cannot load symbol 'poissonCalc': " << dlerror() << '\n';  // Error message if function cannot be loaded
        dlclose(handle);  // Close the library handle
        return 1;
    }

    // Values for the Poisson calculation
    long double lambdas[] = {2, 2, 2, 3, 3};
    int ks[] = {1, 10, 2, 3, 100};

    // Calculate and print the Poisson distribution for each pair of values
    for (int i = 0; i < 5; ++i) {
        long double result = poisson(lambdas[i], ks[i]);  // Calculate the Poisson distribution
        cout.precision(17);
        cout << "Poisson distribution for lambda = " << lambdas[i] << " and k = " << ks[i] << ": " << result << endl;  // Output the result
    }

    // Close the shared library handle
    dlclose(handle);
    return 0;
}
