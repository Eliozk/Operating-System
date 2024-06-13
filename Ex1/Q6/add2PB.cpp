#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
// Function to display an error message and exit the program
void Erry(const char *prog_name) {
    cerr << "Usage: " << prog_name << " \"Name\" \"Last Name\" \"Phone Number\"\n";
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    // Check if the user provided the correct number of arguments
    if (argc != 4) { // Expected format: (program name) (first name) (last name) (phone number)
        Erry(argv[0]);
    }

    // Open the phonebook file in append mode
    ofstream file("phonebook.txt", ios::app);
    if (!file) { // Check if the file was successfully opened
        cerr << "Error: Could not open phonebook.txt\n";
        exit(EXIT_FAILURE);
    }

    // Write the new person's details to the phonebook
    // The format will be: first name last name, phone number then \n
    file << argv[1] << " " << argv[2] << "," << argv[3] << "\n";
    if (file.fail()) { // Check if the write operation was successful
        cerr << "Error: Could not write to phonebook.txt\n";
        exit(EXIT_FAILURE);
    }

    // Close the file
    file.close();

    // Inform the user that the entry was added successfully
    cout << "Phone details added successfully.\n";

    return 0;
}

//to check phone book run "cat phonebook.txt"