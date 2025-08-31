// Benchmark.hpp
#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <chrono>
#include <iostream>

class Benchmark {
public:
    template <typename Func, typename... Args>
    static double measure_time_ms(Func func, Args&&... args) {
        auto start = std::chrono::high_resolution_clock::now();
        func(std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        return duration.count();  // Return duration in milliseconds
    }

    template <typename Func, typename... Args>
    static double measure_time_ns(Func func, Args&&... args) {
        auto start = std::chrono::high_resolution_clock::now();
        func(std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::nano> duration = end - start;
        return duration.count();  // Return duration in nanoseconds
    }
};

#endif // BENCHMARK_HPP
