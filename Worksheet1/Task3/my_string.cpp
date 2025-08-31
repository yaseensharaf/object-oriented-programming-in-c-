#include "my_string.hpp"

// Helper function to release memory when reference count reaches 0
void my_string::release() {
    if (ref_count && --(*ref_count) == 0) { // Decrement reference count and check if it reaches 0
        std::cout << str << " [" << *ref_count << "]" << std::endl;  // Debugging: Print message when memory is being freed
        delete[] str;        // Free the allocated memory for the string
        delete ref_count;    // Free the memory for the reference count
    }
}

// Default constructor
my_string::my_string() : str(nullptr), ref_count(nullptr) {
    // Initializes the string pointer and reference count pointer to nullptr
    // Indicates the object is empty and not managing any memory
}

// Parameterized constructor
my_string::my_string(const char* s) {
    if (s) {
        str = new char[strlen(s) + 1];     // Dynamically allocate memory for the string
        strcpy(str, s);                   // Copy the input string into the allocated memory
        ref_count = new int(1);           // Initialize the reference count to 1 (first reference)
    } else {
        str = nullptr;                    // No input string, set str to nullptr
        ref_count = nullptr;              // No reference count needed, set to nullptr
    }
}

// Copy constructor
my_string::my_string(const my_string& s) {
    str = s.str;             // Copy the pointer to the shared string (shallow copy)
    ref_count = s.ref_count; // Copy the pointer to the reference count
    if (ref_count) {
        ++(*ref_count);      // Increment reference count to account for the new reference
    }
}

// Assignment operator
my_string& my_string::operator=(const my_string& s) {
    if (this != &s) {        // Avoid self-assignment
        release();           // Release the current memory if this object was managing any
        str = s.str;         // Copy the pointer to the shared string (shallow copy)
        ref_count = s.ref_count; // Copy the pointer to the reference count
        if (ref_count) {
            ++(*ref_count);  // Increment reference count for the new assignment
        }
    }
    return *this;            // Return the current object to allow assignment chaining
}

// Destructor
my_string::~my_string() {
    release();               // Release memory if reference count reaches 0
}

// Get character at a specific index
char my_string::getChar(const int& i) const {
    if (str && i >= 0 && i < strlen(str)) { // Ensure the index is valid
        return str[i];                      // Return the character at the given index
    }
    return '\0';                            // Return null character if index is invalid
}

// Set a character at a specific index
void my_string::setChar(const int& i, const char& c) {
    if (str && i >= 0 && i < strlen(str)) { // Ensure the index is valid
        str[i] = c;                         // Update the character at the specified index
    }
}

// Print the string along with the reference count
void my_string::print() const {
    if (str) {
        std::cout << str << " [" << *ref_count << "]" << std::endl; // Print string and current reference count
    } else {
        std::cout << "Empty string" << std::endl; // Handle empty string case
    }
}
