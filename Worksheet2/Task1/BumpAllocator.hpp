#include <cstddef>
#include <new>         // for std::nothrow
#include <mutex>       // for thread-safety
#include <iostream>    // for debug messages

class BumpAllocator {
public:
    // Constructor to allocate the heap with a custom size
    BumpAllocator(std::size_t heap_size) {
        heap = new char[heap_size];  // Create a heap of given size
        next = heap;                 // Initialize the bump pointer to the start of the heap
        heap_end = heap + heap_size; // Calculate the end of the heap
        allocation_count = 0;
        total_allocations = 0;       // Initialize total allocations count
        total_size = heap_size;
        std::cout << "BumpAllocator created with " << heap_size << " bytes." << std::endl;
    }

    // Destructor to clean up the heap memory and display total allocations
    ~BumpAllocator() {
        delete[] heap;
        std::cout << "BumpAllocator destroyed." << std::endl;
        std::cout << "Total allocations made: " << total_allocations << std::endl;
    }

    // Template method to allocate memory for a specific number of objects with alignment
    template <typename T>
    T* alloc(std::size_t num_objects) {
        std::lock_guard<std::mutex> guard(alloc_mutex);  // Lock for thread-safety

        std::size_t required_size = sizeof(T) * num_objects;
        std::size_t alignment = alignof(T);

        // Align the current bump pointer
        char* aligned_ptr = align_pointer(next, alignment);

        // Check if there is enough space to allocate the requested memory
        if (aligned_ptr + required_size <= heap_end) {
            next = aligned_ptr + required_size;  // Move the bump pointer forward
            allocation_count++;                  // Track active allocations
            total_allocations++;                 // Track total allocations made
            std::cout << "Allocated " << required_size << " bytes." << std::endl;
            return reinterpret_cast<T*>(aligned_ptr);
        }

        std::cout << "Failed to allocate memory. Not enough space!" << std::endl;
        return nullptr; // Not enough memory
    }

    // Deallocate memory (reset the allocator when all allocations are freed)
    void dealloc() {
        std::lock_guard<std::mutex> guard(alloc_mutex);  // Lock for thread-safety

        if (allocation_count > 0) {
            allocation_count--;
        }

        // Reset the allocator if all allocations are freed
        if (allocation_count == 0) {
            next = heap;
            std::cout << "Allocator reset." << std::endl;
        }
    }

    // Method to get the remaining available memory
    std::size_t remaining_memory() const {
        return heap_end - next;
    }

private:
    char* heap;               // Pointer to the start of the heap
    char* next;               // Bump pointer indicating the next free location
    char* heap_end;           // Pointer to the end of the heap
    std::size_t total_size;   // Total size of the heap
    std::size_t allocation_count;   // Current active allocations
    std::size_t total_allocations;  // Total allocations ever made
    std::mutex alloc_mutex;         // Mutex for thread-safety

    // Align a pointer to the required alignment
    char* align_pointer(char* ptr, std::size_t alignment) const {
        std::size_t mask = alignment - 1;
        std::size_t misalignment = reinterpret_cast<std::uintptr_t>(ptr) & mask;
        if (misalignment != 0) {
            ptr += (alignment - misalignment); // Move the pointer to the aligned position
        }
        return ptr;
    }
};
