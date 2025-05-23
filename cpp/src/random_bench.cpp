#include <chrono>
#include <numeric>
#include <print>
#include <vector>
#include "random/normal.hpp"
#include "random/uniform.hpp"
#include "random/poisson.hpp"
#include "random/exponential.hpp"
#include "random/stable.h"

using std::vector;

template<typename F>
vector<double> timeit(F f, size_t bench_size) {
    vector<double> result(bench_size);
    for (auto &r : result) {
        auto start_time = std::chrono::high_resolution_clock::now();
        auto res = f();
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        auto elapsed = static_cast<double>(duration.count()) / 1000000000;
        r = elapsed;
    }
    return result;
}

void show_timeit(const vector<double> &result) {
    double mean = std::accumulate(result.begin(), result.end(), 0.0) / result.size();
    double stddev = std::sqrt(std::accumulate(result.begin(), result.end(), 0.0, [mean](double acc, double x) {
        return acc + (x - mean) * (x - mean);
    }) / result.size());
    double min = *std::min_element(result.begin(), result.end());
    double max = *std::max_element(result.begin(), result.end());
    std::println("mean: {}, stddev: {}, min: {}, max: {}", mean, stddev, min, max);
}

int main(int argc, char **argv) {
    size_t bench_size = 10;
    if(argc > 1) {
        bench_size = std::atoi(argv[1]);
    }
    size_t len = 10000000;
    auto stable = [len]() {
        auto result = rand_stable(len, 0.7);
        return *result;
    };

    std::println("stable random numbers generation, unit: s");
    show_timeit(timeit(stable, bench_size));
    return 0;
}
