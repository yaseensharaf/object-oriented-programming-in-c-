#include "my_string.hpp"

int main() {
    // Step 1: Create a my_string object with an initial reference count of 1
    my_string s("Hello world");
    s.print();  // Output: Hello world [1]

    {
        // Step 2: Create a new reference to the same string (copy constructor)
        my_string t = s;
        s.print();  // Output: Hello world [2]
        t.print();  // Output: Hello world [2]

        // Step 3: Display the second character in the string
        std::cout << s.getChar(1) << std::endl;  // Output: 'e'
        s.print();  // Output: Hello world [2]
        t.print();  // Output: Hello world [2]
    }  // Step 4: 't' goes out of scope here, so reference count should decrease to 1
    // We should see: Hello world [1]

    // Step 5: Modify the string through 's'
    s.setChar(1, 'E');  // Modify the second character to 'E'
    s.print();  // Output: HEllo world [1]

    {
        // Step 6: Create another reference 'u' from 's'
        my_string u = s;
        s.print();  // Output: HEllo world [2]
        u.print();  // Output: HEllo world [2]

        {
            // Step 7: Create a third reference 'v' from 's' (increment reference count to 3)
            my_string v = s;
            s.print();  // Output: HEllo world [3]
            u.print();  // Output: HEllo world [3]
            v.print();  // Output: HEllo world [3]
        }  // Step 8: 'v' goes out of scope, reference count decreases to 2

        s.print();  // Output: HEllo world [2]
    }  // Step 9: 'u' goes out of scope, reference count decreases back to 1
    // We should see: HEllo world [1]

    // Step 10: At the end of the program, 's' goes out of scope and reference count reaches 0
    // We should see the output: HEllo world [0]
}
