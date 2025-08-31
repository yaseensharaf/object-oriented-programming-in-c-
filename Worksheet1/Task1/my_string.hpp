#include <iostream>
#include <cstring>

using namespace std;
class my_string {
public:
    char*str;
    my_string();
    my_string(const char*);
    my_string(my_string const& s);
    my_string& operator= (my_string const& s);
    ~my_string();

    char getChar(const int& i) const;
    void setChar(const int& i, const char& c);
    void print() const;
};