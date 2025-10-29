#include <chrono>
#include <thread>
#include <utility>
#include <vector>
#include <print>
#include <ranges>
#include "random/normal.hpp"

using std::vector;

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

struct Bm {
    double starting_position = 0.0;
    double diffusivity = 0.5;
    Bm() = default;
    Bm(double starting_position, double diffusivity) : starting_position(starting_position), diffusivity(diffusivity) {}
    
    [[nodiscard]] auto simulate(double duration, double tau = 0.01) const -> std::pair<vector<double>, vector<double>> {
        vector<double> t = linspace(0.0, duration, tau);
        size_t n = t.size() - 1;
        vector<double> x(n+1);
        x[0] = starting_position;
        double sigma = std::sqrt(2 * diffusivity * tau);
        auto noise = randn(n).value();
        for (size_t i = 0; i < n; ++i) {
           x[i+1] = x[i] + (sigma * noise[i]);
        }
        return std::make_pair(t, x);
    }

    [[nodiscard]] auto msd(double duration, double tau=0.01, size_t particles=10000) const -> double {
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
            threads.emplace_back([this, i, start, end, duration, tau, &partial_results]() -> void {
                double local_sum = 0.0;
                for(size_t j = start; j < end; ++j) {
                    auto [t, x] = simulate(duration, tau);
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
};

int main() {
    Bm bm {};
    auto duration = std::views::iota(1, 11) | std::views::transform([](int v) -> double {
        return static_cast<double>(v * 100);
    });
    auto func = [&]() -> int {
        for(const double& d: duration) {
            double m = bm.msd(d);
        }
        return 0;
    };
    auto elapsed = timeit(func);
    std::println("Elapsed {}s", elapsed);
    return 0;
}
