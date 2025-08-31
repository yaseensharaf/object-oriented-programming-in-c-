#include <iostream>
#include "BumpAllocator.hpp"

int main() {
    // Create a bump allocator with 1024 bytes of memory
    BumpAllocator allocator(1024);

    // Test 1: Allocate space for 10 integers (40 bytes)
    std::cout << "\n--- Test 1: Allocate 10 integers ---" << std::endl;
    int* int_ptr = allocator.alloc<int>(10);
    if (int_ptr != nullptr) {
        for (int i = 0; i < 10; ++i) {
            int_ptr[i] = i * 10;
        }
        // Print the allocated integers
        std::cout << "Allocated integers: ";
        for (int i = 0; i < 10; ++i) {
            std::cout << int_ptr[i] << " ";
        }
        std::cout << std::endl;
    } else {
        std::cerr << "Failed to allocate memory for 10 integers!" << std::endl;
    }

    // Test 2: Allocate space for 20 floats (80 bytes)
    std::cout << "\n--- Test 2: Allocate 20 floats ---" << std::endl;
    float* float_ptr = allocator.alloc<float>(20);
    if (float_ptr != nullptr) {
        for (int i = 0; i < 20; ++i) {
            float_ptr[i] = i * 0.5f;
        }
        // Print the allocated floats
        std::cout << "Allocated floats: ";
        for (int i = 0; i < 20; ++i) {
            std::cout << float_ptr[i] << " ";
        }
        std::cout << std::endl;
    } else {
        std::cerr << "Failed to allocate memory for 20 floats!" << std::endl;
    }

    // Check remaining memory after the first two allocations
    std::cout << "Remaining memory after Test 2: " << allocator.remaining_memory() << " bytes" << std::endl;

    // Test 3: Attempt to allocate more memory than available
    std::cout << "\n--- Test 3: Allocate 200 doubles (should fail due to insufficient memory) ---" << std::endl;
    double* double_ptr = allocator.alloc<double>(200);  // This requires 1600 bytes, more than available
    if (double_ptr == nullptr) {
        std::cout << "Failed to allocate memory for 200 doubles as expected!" << std::endl;
    }

    // Reset the allocator and make a new allocation to verify reset functionality
    allocator.dealloc();  // Reset all allocations
    std::cout << "\nAllocator reset.\n\n";

    // New allocation after reset
    std::cout << "--- Test 4: Allocate 5 new integers after reset ---" << std::endl;
    int* new_int_ptr = allocator.alloc<int>(5);
    if (new_int_ptr != nullptr) {
        for (int i = 0; i < 5; ++i) {
            new_int_ptr[i] = i + 1;
        }
        // Print the new allocated integers
        std::cout << "New allocated integers after reset: ";
        for (int i = 0; i < 5; ++i) {
            std::cout << new_int_ptr[i] << " ";
        }
        std::cout << std::endl;
    } else {
        std::cerr << "Failed to allocate memory for new 5 integers after reset!" << std::endl;
    }

    return 0;
}
