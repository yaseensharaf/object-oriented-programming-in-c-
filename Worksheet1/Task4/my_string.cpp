// my_string.cpp
#include "my_string.hpp"

// Default constructor
my_string::my_string() : str_ref(nullptr) {}

// Parameterized constructor
my_string::my_string(const char* s) {
    if (s) {
        char* str = new char[strlen(s) + 1];  // Allocate memory for the string
        strcpy(str, s);                       // Copy the input string
        str_ref = ReferenceCounted<char>(str);  // Initialize reference counted object
    }
}

// Copy constructor
my_string::my_string(const my_string& s) : str_ref(s.str_ref) {}

// Assignment operator
my_string& my_string::operator=(const my_string& s) {
    if (this != &s) {
        str_ref = s.str_ref;  // Copy the reference counted object
    }
    return *this;
}

// Destructor
my_string::~my_string() {
    // No manual memory management needed, handled by ReferenceCounted
}

// Get character at a specific index
char my_string::getChar(const int& i) const {
    if (str_ref.get() && i >= 0 && i < strlen(str_ref.get())) {
        return str_ref.get()[i];
    }
    return '\0';  // Return null character if index is out of bounds
}

// Set a character at a specific index
void my_string::setChar(const int& i, const char& c) {
    if (str_ref.get() && i >= 0 && i < strlen(str_ref.get())) {
        str_ref.get()[i] = c;
    }
}

// Print the string along with the reference count
void my_string::print() const {
    if (str_ref.get()) {
        std::cout << str_ref.get() << " [" << str_ref.get_ref_count() << "]" << std::endl;
    } else {
        std::cout << "Empty string" << std::endl;
    }
}
