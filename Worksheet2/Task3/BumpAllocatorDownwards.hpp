#ifndef BUMPALLOCATORDOWNWARDS_HPP
#define BUMPALLOCATORDOWNWARDS_HPP

#include <cstddef>  // For size_t
#include <mutex>    // For thread-safety using std::mutex
#include <iostream> // For debug messages

// Class defining a downward bump allocator
class BumpAllocatorDownwards {
public:
    // Constructor: Initializes the allocator with a fixed heap size
    BumpAllocatorDownwards(std::size_t heap_size) {
        heap = new char[heap_size];      // Allocate memory for the heap
        next = heap + heap_size;         // Set the bump pointer to the end of the heap
        heap_end = heap + heap_size;     // Mark the end of the heap
        heap_start = heap;               // Mark the start of the heap
        allocation_count = 0;            // Initialize allocation counter
        total_allocations = 0;           // Initialize total allocations counter
        // Debug message (commented out for cleaner output)
        // std::cout << "BumpAllocatorDownwards created with " << heap_size << " bytes." << std::endl;
    }

    // Destructor: Cleans up allocated memory
    ~BumpAllocatorDownwards() {
        delete[] heap; // Free the allocated heap memory
        // Debug message (commented out for cleaner output)
        // std::cout << "BumpAllocatorDownwards destroyed. Total allocations made: " << total_allocations << std::endl;
    }

    // Template function for memory allocation
    template <typename T>
    T* alloc(std::size_t num_objects) {
        std::lock_guard<std::mutex> guard(alloc_mutex); // Ensure thread-safety

        std::size_t required_size = sizeof(T) * num_objects; // Calculate required memory size
        std::size_t alignment = alignof(T);                 // Get alignment for the data type

        // Align the pointer by moving it backward
        char* aligned_ptr = align_pointer(next - required_size, alignment);

        // Check if the aligned pointer is within bounds
        if (aligned_ptr >= heap_start) {
            next = aligned_ptr;       // Update the bump pointer
            allocation_count++;       // Increment the current allocation count
            total_allocations++;      // Increment the total allocations count
            // Debug message (commented out for cleaner output)
            // std::cout << "Allocated " << required_size << " bytes." << std::endl;
            return reinterpret_cast<T*>(aligned_ptr); // Return aligned pointer cast to T*
        }

        // If allocation fails (out of memory), print an error message
        std::cout << "Failed to allocate memory. Not enough space!" << std::endl;
        return nullptr; // Return null pointer if allocation fails
    }

    // Function to deallocate memory
    void dealloc() {
        std::lock_guard<std::mutex> guard(alloc_mutex); // Ensure thread-safety

        if (allocation_count > 0) {
            allocation_count--; // Decrease allocation count
        }

        // Reset the allocator if all allocations are deallocated
        if (allocation_count == 0) {
            next = heap_end;    // Reset the bump pointer to the end of the heap
            std::cout << "Allocator reset." << std::endl; // Debug message
        }
    }

    // Function to get the remaining memory available
    std::size_t remaining_memory() const {
        return next - heap_start; // Calculate remaining memory by subtracting pointers
    }

private:
    char* heap;               // Pointer to the start of the heap
    char* next;               // Bump pointer for the next allocation
    char* heap_end;           // Pointer to the end of the heap
    char* heap_start;         // Pointer to the start of the heap
    std::size_t allocation_count; // Number of active allocations
    std::size_t total_allocations; // Total number of allocations ever made
    std::mutex alloc_mutex;   // Mutex for thread-safety

    // Function to align a pointer to the required alignment
    char* align_pointer(char* ptr, std::size_t alignment) const {
        std::size_t mask = alignment - 1;                   // Create alignment mask
        std::size_t misalignment = reinterpret_cast<std::uintptr_t>(ptr) & mask; // Calculate misalignment
        if (misalignment != 0) {
            ptr -= misalignment; // Adjust the pointer backward to align
        }
        return ptr; // Return aligned pointer
    }
};

#endif // BUMPALLOCATORDOWNWARDS_HPP
