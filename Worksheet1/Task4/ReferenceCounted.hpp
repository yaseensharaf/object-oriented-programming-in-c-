// ReferenceCounted.hpp
#ifndef REFERENCE_COUNTED_HPP
#define REFERENCE_COUNTED_HPP

#include <iostream>

template<typename T>
class ReferenceCounted {
private:
    T* object;           // Pointer to the managed object
    int* ref_count;      // Pointer to reference count

    void release() {
        if (ref_count && --(*ref_count) == 0) {
            // Memory release (no message for release)
            delete object;        // Free the object memory
            delete ref_count;     // Free the reference count memory
        } else if (ref_count) {
            std::cout << "Reference count decreased: " << *ref_count << std::endl;
        }
    }

public:
    // Constructor that accepts a raw pointer to an object
    ReferenceCounted(T* obj = nullptr) : object(obj), ref_count(nullptr) {
        if (object) {
            ref_count = new int(1);  // Initialize reference count to 1
            std::cout << "Reference count initialized: " << *ref_count << std::endl;
        }
    }

    // Copy constructor
    ReferenceCounted(const ReferenceCounted& other) {
        object = other.object;         // Shallow copy the object pointer
        ref_count = other.ref_count;   // Share the reference count
        if (ref_count) {
            ++(*ref_count);            // Increment reference count
            std::cout << "Reference count increased: " << *ref_count << std::endl;
        }
    }

    // Assignment operator
    ReferenceCounted& operator=(const ReferenceCounted& other) {
        if (this != &other) {
            release();                // Release the current object if needed
            object = other.object;    // Shallow copy the object pointer
            ref_count = other.ref_count;  // Share the reference count
            if (ref_count) {
                ++(*ref_count);       // Increment reference count
                std::cout << "Reference count increased: " << *ref_count << std::endl;
            }
        }
        return *this;
    }

    // Destructor
    ~ReferenceCounted() {
        release();  // Release the object when ref count reaches 0
    }

    // Access the underlying object
    T* get() const {
        return object;
    }

    // Dereference operator to access members of the object
    T& operator*() const {
        return *object;
    }

    // Pointer access operator
    T* operator->() const {
        return object;
    }

    // Get current reference count
    int get_ref_count() const {
        return ref_count ? *ref_count : 0;
    }
};

#endif // REFERENCE_COUNTED_HPP
