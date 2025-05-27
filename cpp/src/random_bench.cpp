#include <algorithm>
#include <chrono>
#include <numeric>
#include <print>
#include <vector>
#include <fstream>
#include <filesystem>

#include "random/normal.hpp"
#include "random/uniform.hpp"
#include "random/poisson.hpp"
#include "random/exponential.hpp"
#include "random/stable.h"

using std::vector;

constexpr double NANOSECONDS_PER_SECOND = 1000000000.0;

template<typename F>
auto timeit(F func, size_t bench_size) -> vector<double> {
    vector<double> result(bench_size);
    for (auto &val : result) {
        auto start_time = std::chrono::high_resolution_clock::now();
        auto res = func();
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        auto elapsed = static_cast<double>(duration.count()) / NANOSECONDS_PER_SECOND;
        val = elapsed;
    }
    return result;
}

void show_timeit(const vector<double> &result, std::ofstream &log_file) {
    double mean = std::accumulate(result.begin(), result.end(), 0.0) / result.size();
    double stddev = std::sqrt(std::accumulate(result.begin(), result.end(), 0.0, [mean](double acc, double x) {
        return acc + ((x - mean) * (x - mean));
    }) / result.size());
    double min = *std::ranges::min_element(result);
    double max = *std::ranges::max_element(result);
    
    std::println(log_file, "mean: {:.4f}, stddev: {:.4f}, min: {:.4f}, max: {:.4f}", mean, stddev, min, max);
    std::println(log_file, "");
}

int main(int argc, char **argv) {
    size_t bench_size = 20;
    if(argc > 1) {
        bench_size = std::atoi(argv[1]);
    }
    size_t len = 10000000;

    // 创建log目录（如果不存在）
    std::filesystem::create_directories("../../log");
    
    // 打开日志文件
    std::ofstream log_file("../../log/cpp.log");
    if (!log_file.is_open()) {
        std::println(stderr, "Error: Could not open log file ../../log/cpp.log");
        return 1;
    }

    auto uniform = [len]() {
        auto result = rand(len);
        return *result;
    };

    auto stable = [len]() {
        auto result = rand_stable(len, 0.7);
        return *result;
    };

    auto normal = [len]() {
        auto result = randn(len);
        return *result;
    };
    
    std::println(log_file, "==========================C++==========================");
    std::println(log_file, "");
    
    std::println(log_file, "bench size: {}, length of random vectors: {}", bench_size, len);
    std::println(log_file, "unit: second");
    std::println(log_file, "");
    
    std::println(log_file, "-----------uniform random number sampling--------------");
    show_timeit(timeit(uniform, bench_size), log_file);

    std::println(log_file, "------------normal random number sampling--------------");
    show_timeit(timeit(normal, bench_size), log_file);

    std::println(log_file, "-----------stable random number sampling---------------");
    show_timeit(timeit(stable, bench_size), log_file);

    std::println(log_file, "=======================================================");
    std::println(log_file, "");
    
    // 关闭日志文件
    log_file.close();
    return 0;
}
