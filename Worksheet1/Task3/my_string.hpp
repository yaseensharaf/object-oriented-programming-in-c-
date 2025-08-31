#include <iostream>
#include <cstring>

class my_string {
private:
    char* str;           // Pointer to the string data
    int* ref_count;      // Pointer to reference count

    // Helper function to release memory when reference count is 0
    void release();

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

