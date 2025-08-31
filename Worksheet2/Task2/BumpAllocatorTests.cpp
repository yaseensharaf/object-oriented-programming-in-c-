// BumpAllocatorTests.cpp
#include "BumpAllocator.hpp"
#include "simpletest/simpletest.h"
#include <iostream>

using namespace std;

char const *groups[] = {
    "BumpAllocatorTests",
};

// Test: Single allocation and deallocation
DEFINE_TEST_G(SingleAllocationAndDeallocation, BumpAllocatorTests) {
    BumpAllocator allocator(20, false); // Small allocator with 20 bytes

    int* int_ptr = allocator.alloc<int>(1); // Allocate 4 bytes for 1 integer
    TEST_MESSAGE(int_ptr != nullptr, "Failed to allocate memory for a single integer!");

    allocator.dealloc(); // Reset the allocator
    TEST_MESSAGE(allocator.remaining_memory() == 20, "Allocator did not reset correctly after single allocation deallocation!");
}

// Test: Multiple small allocations
DEFINE_TEST_G(MultipleSmallAllocations, BumpAllocatorTests) {
    BumpAllocator allocator(50, false); // Small allocator with 50 bytes

    int* int_ptr1 = allocator.alloc<int>(1); // 4 bytes
    int* int_ptr2 = allocator.alloc<int>(1); // Another 4 bytes
    int* int_ptr3 = allocator.alloc<int>(1); // Another 4 bytes
    TEST_MESSAGE(int_ptr1 != nullptr && int_ptr2 != nullptr && int_ptr3 != nullptr, "Failed small allocations!");

    // Remaining memory should be 38 bytes
    TEST_MESSAGE(allocator.remaining_memory() == 38, "Remaining memory not as expected after small allocations.");
}

// Test: Alignment for different types
DEFINE_TEST_G(AlignmentTest, BumpAllocatorTests) {
    BumpAllocator allocator(40, false); // Small allocator with 40 bytes

    char* char_ptr = allocator.alloc<char>(1); // 1 byte
    int* int_ptr = allocator.alloc<int>(1);     // 4 bytes
    double* double_ptr = allocator.alloc<double>(1); // 8 bytes
    TEST_MESSAGE(char_ptr != nullptr && int_ptr != nullptr && double_ptr != nullptr, "Failed allocation with alignment!");

    // Remaining memory should reflect the aligned allocations
    TEST_MESSAGE(allocator.remaining_memory() < 40, "Remaining memory does not match expected value after aligned allocations.");
}

// Test: Allocation failure due to insufficient memory (simplified)
DEFINE_TEST_G(AllocationExceedsMemory, BumpAllocatorTests) {
    BumpAllocator allocator(50, false); // Small allocator with only 50 bytes available

    // Attempt to allocate more than the available memory (60 bytes for 15 integers)
    int* int_ptr = allocator.alloc<int>(15); // Requires 60 bytes, exceeds the 50-byte limit

    // Expecting nullptr since allocation exceeds available memory
    TEST_MESSAGE(int_ptr == nullptr, "Allocation succeeded unexpectedly when exceeding memory limit!");
}

// Test: Exact fit allocation
DEFINE_TEST_G(ExactFitAllocation, BumpAllocatorTests) {
    BumpAllocator allocator(40, false); // 40 bytes total

    int* int_ptr = allocator.alloc<int>(10); // Should fit exactly, allocating all 40 bytes
    TEST_MESSAGE(int_ptr != nullptr, "Failed to allocate memory for 10 integers with exact fit!");

    size_t remaining_memory = allocator.remaining_memory();
    TEST_MESSAGE(remaining_memory == 0, "Remaining memory not zero after exact fit allocation.");
}

// Test: Allocation within bounds and remaining memory check
DEFINE_TEST_G(AllocationWithinBounds, BumpAllocatorTests) {
    BumpAllocator allocator(100, false); // Allocator with 100 bytes

    int* int_ptr = allocator.alloc<int>(10); // Allocates 40 bytes for 10 integers
    TEST_MESSAGE(int_ptr != nullptr, "Failed to allocate memory for 10 integers within bounds!");

    float* float_ptr = allocator.alloc<float>(10); // Allocates 40 bytes for 10 floats
    TEST_MESSAGE(float_ptr != nullptr, "Failed to allocate memory for 10 floats within bounds!");

    // Check remaining memory should be 20 bytes
    size_t remaining_memory = allocator.remaining_memory();
    TEST_MESSAGE(remaining_memory == 20, "Remaining memory does not match expected value of 20 bytes.");
}

// Test: Reset allocator and verify reallocation after deallocation
DEFINE_TEST_G(ResetAndReallocation, BumpAllocatorTests) {
    BumpAllocator allocator(100, false); // Initialize with 100 bytes

    int* int_ptr = allocator.alloc<int>(10); // Allocates 40 bytes for 10 integers
    TEST_MESSAGE(int_ptr != nullptr, "Failed to allocate memory for 10 integers within bounds!");

    allocator.dealloc(); // Reset the allocator
    TEST_MESSAGE(allocator.remaining_memory() == 100, "Allocator did not reset correctly after deallocation!");

    int* new_int_ptr = allocator.alloc<int>(5); // Allocate 20 bytes after reset
    TEST_MESSAGE(new_int_ptr != nullptr, "Failed to allocate memory after reset!");
}

// Test: Small heap memory exceeded
DEFINE_TEST_G(SmallHeapMemoryExceeded, BumpAllocatorTests) {
    BumpAllocator allocator(10, false); // Very small allocator with 10 bytes

    int* int_ptr = allocator.alloc<int>(3); // Request 12 bytes, which exceeds 10
    TEST_MESSAGE(int_ptr == nullptr, "Allocation succeeded unexpectedly on small heap exceeding available memory!");
}

int main() {
    bool pass = true;
    for (auto group : groups) {
        pass &= TestFixture::ExecuteTestGroup(group, TestFixture::Verbose);
    }
    return pass ? 0 : 1;
}
