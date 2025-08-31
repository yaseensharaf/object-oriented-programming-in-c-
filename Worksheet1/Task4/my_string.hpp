// my_string.hpp
#ifndef MY_STRING_HPP
#define MY_STRING_HPP

#include <iostream>
#include <cstring>
#include "ReferenceCounted.hpp"

class my_string {
private:
    ReferenceCounted<char> str_ref;  // Use ReferenceCounted to manage char*

public:
    // Default constructor
    my_string();

    // Parameterized constructor
    my_string(const char*);

    // Copy constructor
    my_string(const my_string& s);

    // Assignment operator
    my_string& operator=(const my_string& s);

    // Destructor
    ~my_string();

    // Get a character at a specific index
    char getChar(const int& i) const;

    // Set a character at a specific index
    void setChar(const int& i, const char& c);

    // Print the string along with the reference count
    void print() const;
};

#endif // MY_STRING_HPP
