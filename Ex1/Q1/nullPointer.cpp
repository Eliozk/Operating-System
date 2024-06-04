#include <iostream>

int main() {
    int* ptr = nullptr; // Initializing a pointer to nullptr (null pointer)

    // Attempting to dereference the null pointer
    // This will result in undefined behavior
    std::cout << "Value at nullptr: " << *ptr << std::endl;

    // Writing to an undefined memory address (wild pointer)
    // This can lead to crashes or unexpected behavior
    int* wildPtr = reinterpret_cast<int*>(0xDEADBEEF);
    *wildPtr = 42;

    return 0;
}
