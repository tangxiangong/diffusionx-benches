#ifndef DIFFUSIONX_BENCHES_UTILS_HPP
#define DIFFUSIONX_BENCHES_UTILS_HPP

#include <vector>
#include <thread>
#include <concepts>
#include <chrono>

using std::vector;

template<typename T>
concept Simulator = std::invocable<T> &&
    std::same_as<std::invoke_result_t<T>, std::pair<vector<double>, vector<double>>>;


constexpr double NANOSECONDS_PER_SECOND = 1000000000.0;

template<typename F>
auto timeit(F func) -> double {
    auto start_time = std::chrono::high_resolution_clock::now();
    auto res = func();
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    auto elapsed = static_cast<double>(duration.count()) / NANOSECONDS_PER_SECOND;

    return elapsed;
}

auto linspace(double start, double end, double step) -> vector<double> {
    vector<double> result;
    for (double val = start; val <= end; val += step) {
        result.push_back(val);
    }
    if (std::abs(result.back()-end) > 1e-5) {
        result.push_back(end);
    } else {
        result.back() = end;
    }
    return result;
}

template<Simulator T>
auto mc_msd(size_t particles, T simulate) -> double {
    unsigned int num_threads = std::thread::hardware_concurrency();
    vector<std::thread> threads;
    threads.reserve(num_threads);

    vector<double> partial_results(num_threads, 0.0);

    size_t chunk_size = particles / num_threads;
    size_t remainder = particles % num_threads;

    for(size_t i = 0; i < num_threads; ++i) {
        size_t start = i*chunk_size;
        size_t end = start + chunk_size;
        if(i == num_threads - 1) {
            end += remainder;
        }
        // Explicit capture - copy this to avoid shared pointer access
        threads.emplace_back([i, start, end, &partial_results, &simulate]() -> void {
            double local_sum = 0.0;
            for(size_t j = start; j < end; ++j) {
                auto [t, x] = simulate();
                double dx = x.back() - x.front();
                local_sum += (dx * dx);
            }
            partial_results[i] = local_sum;
        });
    }

    for(auto& thread : threads) {
        thread.join();
    }

    double total_sum = 0.0;
    for(double partial: partial_results) {
        total_sum += partial;
    }
    return total_sum / static_cast<double>(particles);
}

#endif //DIFFUSIONX_BENCHES_UTILS_HPP
