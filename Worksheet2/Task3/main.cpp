#include "BumpAllocatorUpwards.hpp"
#include "BumpAllocatorDownwards.hpp"
#include "Benchmark.hpp"
#include <iostream>

//Add small allocation function for benchmarking small-sized memory allocations.
template <typename Allocator>
void small_allocations(Allocator& allocator) {
    for (int i = 0; i < 1000; ++i) {
        allocator.template alloc<int>(1);  // Allocate memory for one integer 1000 times.
    }
    allocator.dealloc();  // Reset the allocator after allocations.
}

//Add large allocation function to benchmark scenarios with larger memory blocks.
template <typename Allocator>
void large_allocations(Allocator& allocator) {
    for (int i = 0; i < 10; ++i) {
        allocator.template alloc<int>(100);  // Allocate memory for 100 integers 10 times.
    }
    allocator.dealloc();  // Reset the allocator after allocations.
}

//Add mixed allocation function to test allocators with a combination of small and large allocations.
template <typename Allocator>
void mixed_allocations(Allocator& allocator) {
    for (int i = 0; i < 500; ++i) {
        allocator.template alloc<int>(1);  // Small allocations: 500 integers.
    }
    for (int i = 0; i < 5; ++i) {
        allocator.template alloc<int>(200);  // Large allocations: 5 blocks of 200 integers.
    }
    allocator.dealloc();  // Reset the allocator after allocations.
}

//Add custom tests to simulate real-world allocation scenarios with multiple data types.
template <typename Allocator>
void custom_tests(Allocator& allocator) {
    allocator.template alloc<int>(50);    // Allocate memory for 50 integers.
    allocator.template alloc<double>(20); // Allocate memory for 20 doubles.
    allocator.template alloc<float>(100); // Allocate memory for 100 floats.
    allocator.dealloc();  // Reset the allocator after allocations.
}

int main() {
    //Initialize upward and downward bump allocators with 1MB of memory.
    BumpAllocatorUpwards allocator_up(1024 * 1024);      // 1 MB Upward Allocator.
    BumpAllocatorDownwards allocator_down(1024 * 1024);  // 1 MB Downward Allocator.

    //Benchmark upward bump allocator for all test cases.
    std::cout << "UpwardBumpAllocator:\n";
    double up_time_ms = Benchmark::measure_time_ms(small_allocations<BumpAllocatorUpwards>, allocator_up);
    double up_time_ns = Benchmark::measure_time_ns(small_allocations<BumpAllocatorUpwards>, allocator_up);
    std::cout << "Small Allocations - Up: " << up_time_ms << " ms (" << up_time_ns << " ns)\n";

    up_time_ms = Benchmark::measure_time_ms(large_allocations<BumpAllocatorUpwards>, allocator_up);
    up_time_ns = Benchmark::measure_time_ns(large_allocations<BumpAllocatorUpwards>, allocator_up);
    std::cout << "Large Allocations - Up: " << up_time_ms << " ms (" << up_time_ns << " ns)\n";

    up_time_ms = Benchmark::measure_time_ms(mixed_allocations<BumpAllocatorUpwards>, allocator_up);
    up_time_ns = Benchmark::measure_time_ns(mixed_allocations<BumpAllocatorUpwards>, allocator_up);
    std::cout << "Mixed Allocations - Up: " << up_time_ms << " ms (" << up_time_ns << " ns)\n";

    up_time_ms = Benchmark::measure_time_ms(custom_tests<BumpAllocatorUpwards>, allocator_up);
    up_time_ns = Benchmark::measure_time_ns(custom_tests<BumpAllocatorUpwards>, allocator_up);
    std::cout << "Custom Tests - Up: " << up_time_ms << " ms (" << up_time_ns << " ns)\n";

    //Benchmark downward bump allocator for all test cases.
    std::cout << "\nDownwardBumpAllocator:\n";
    double down_time_ms = Benchmark::measure_time_ms(small_allocations<BumpAllocatorDownwards>, allocator_down);
    double down_time_ns = Benchmark::measure_time_ns(small_allocations<BumpAllocatorDownwards>, allocator_down);
    std::cout << "Small Allocations - Down: " << down_time_ms << " ms (" << down_time_ns << " ns)\n";

    down_time_ms = Benchmark::measure_time_ms(large_allocations<BumpAllocatorDownwards>, allocator_down);
    down_time_ns = Benchmark::measure_time_ns(large_allocations<BumpAllocatorDownwards>, allocator_down);
    std::cout << "Large Allocations - Down: " << down_time_ms << " ms (" << down_time_ns << " ns)\n";

    down_time_ms = Benchmark::measure_time_ms(mixed_allocations<BumpAllocatorDownwards>, allocator_down);
    down_time_ns = Benchmark::measure_time_ns(mixed_allocations<BumpAllocatorDownwards>, allocator_down);
    std::cout << "Mixed Allocations - Down: " << down_time_ms << " ms (" << down_time_ns << " ns)\n";

    down_time_ms = Benchmark::measure_time_ms(custom_tests<BumpAllocatorDownwards>, allocator_down);
    down_time_ns = Benchmark::measure_time_ns(custom_tests<BumpAllocatorDownwards>, allocator_down);
    std::cout << "Custom Tests - Down: " << down_time_ms << " ms (" << down_time_ns << " ns)\n";

    //Finalize benchmarking with performance results for both allocators.
    return 0;
}
