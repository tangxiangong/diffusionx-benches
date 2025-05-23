#include <chrono>
#include <print>
#include "random/stable.h"

int main() {
    size_t len = 10000000;
    auto start_time = std::chrono::high_resolution_clock::now();

    auto result = rand_stable(len, 0.7);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    auto elapsed = static_cast<double>(duration.count()) / 1000000000;
    std::println("Time taken by C++: {} s", elapsed);

    if (!result) {
        std::println("error: {}", result.error().message);
        return 1;
    }

    return 0;
}
