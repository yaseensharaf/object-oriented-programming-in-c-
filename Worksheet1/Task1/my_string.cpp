#include "my_string.hpp"

// Default constructor
my_string::my_string() : str(nullptr) {
    // Initializes the string pointer to nullptr, indicating an empty string
    // Ensures the object starts in a valid state
}

// Parameterized constructor
my_string::my_string(const char* s) {
    if (s) {
        // Allocate memory for the input string plus a null terminator
        str = new char[strlen(s) + 1];
        // Copy the input string into the allocated memory
        strcpy(str, s);
    } else {
        // If the input string is nullptr, set the internal pointer to nullptr
        str = nullptr;
    }
}

// Copy constructor (shallow copy)
my_string::my_string(const my_string& s) {
    // Copies the pointer of the string from the source object
    // Both objects will now share the same memory
    str = s.str;
}

// Assignment operator (shallow copy)
my_string& my_string::operator=(const my_string& s) {
    if (this != &s) { // Check for self-assignment
        // Copy the pointer of the string from the source object
        // This performs a shallow copy, meaning memory is shared
        str = s.str;
    }
    // Return the current object to allow chaining of assignments
    return *this;
}

// Destructor (empty for now)
my_string::~my_string() {
    // No memory deallocation happens here
    // Memory leaks will occur because the dynamically allocated memory is not freed
    // Proper cleanup will be implemented in later tasks
}

// Get character at a specific index
char my_string::getChar(const int& i) const {
    if (str && i >= 0 && i < strlen(str)) { // Boundary check for valid index
        return str[i]; // Return the character at the given index
    }
    return '\0'; // Return null character if index is out of bounds or string is empty
}

// Set a character at a specific index
void my_string::setChar(const int& i, const char& c) {
    if (str && i >= 0 && i < strlen(str)) { // Boundary check for valid index
        str[i] = c; // Update the character at the specified index
    }
    // If the index is invalid, no changes are made to the string
}

// Print the string
void my_string::print() const {
    if (str) {
        // Print the string if it is not empty
        std::cout << str << std::endl;
    } else {
        // Print a message indicating the string is empty
        std::cout << "Empty string" << std::endl;
    }
}
