#include "my_string.hpp"

// Helper function to release memory when reference count reaches 0
void my_string::release() {
    if (ref_count && --(*ref_count) == 0) { // Decrement the reference count
        delete[] str;        // Free the allocated string memory when no references remain
        delete ref_count;    // Free the reference count memory
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
        str = new char[strlen(s) + 1];     // Allocate memory for the string
        strcpy(str, s);                   // Copy the input string into the allocated memory
        ref_count = new int(1);           // Initialize the reference count to 1
    } else {
        str = nullptr;                    // No string provided, set to nullptr
        ref_count = nullptr;              // No reference count needed
    }
}

// Copy constructor
my_string::my_string(const my_string& s) {
    str = s.str;             // Shallow copy the string pointer
    ref_count = s.ref_count; // Copy the pointer to the shared reference count
    if (ref_count) {
        ++(*ref_count);      // Increment the reference count to reflect the new reference
    }
}

// Assignment operator
my_string& my_string::operator=(const my_string& s) {
    if (this != &s) {        // Avoid self-assignment
        release();           // Release the current memory if this object was managing any
        str = s.str;         // Shallow copy the string pointer
        ref_count = s.ref_count; // Copy the reference count pointer
        if (ref_count) {
            ++(*ref_count);  // Increment the reference count
        }
    }
    return *this;            // Return the current object for chaining
}

// Destructor
my_string::~my_string() {
    release();               // Call the helper function to release memory if reference count reaches 0
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
        // Print the string and its reference count
        std::cout << str << " [" << *ref_count << "]" << std::endl;
    } else {
        // Indicate the string is empty
        std::cout << "Empty string" << std::endl;
    }
}