#include "ReferenceCounted.hpp"
#include "my_string.hpp"

// Defining the point class directly in main.cpp
class point {
public:
    int x, y;
    point(int a, int b) : x(a), y(b) {}

    void print() const {
        std::cout << "Point (" << x << ", " << y << ")" << std::endl;
    }
};

int main() {
    // Test with int
    ReferenceCounted<int> intRef(new int(10));
    std::cout << "int value: " << *intRef.get() << std::endl;

    {
        ReferenceCounted<int> intRef2 = intRef;  // Copy constructor
    }  // intRef2 goes out of scope

    // Test with double
    ReferenceCounted<double> doubleRef(new double(3.14159));
    std::cout << "double value: " << *doubleRef.get() << std::endl;

    {
        ReferenceCounted<double> doubleRef2 = doubleRef;  // Copy constructor
    }  // doubleRef2 goes out of scope

    // Test with custom class point
    ReferenceCounted<point> pointRef(new point(5, 10));
    pointRef.get()->print();

    {
        ReferenceCounted<point> pointRef2 = pointRef;  // Copy constructor
        pointRef2.get()->print();
    }  // pointRef2 goes out of scope

    // Test with my_string
    my_string s("Hello, Template");
    s.print();

    {
        my_string t = s;  // Copy constructor
        t.print();
        s.print();
    }  // t goes out of scope

    s.setChar(1, 'E');
    s.print();

    return 0;
}
