#include "utils.hpp"
#include <print>
#include <ranges>
#include <vector>

import diffusionx.simulation.continuous;

using std::vector;

int main() {
  // 定义漂移和扩散函数
  auto drift = [](double x, double t) -> double { return -x; };
  auto diffusivity = [](double x, double t) -> double { return 1.0; };

  // 创建 Langevin 方程
  Langevin eq{drift, diffusivity, 0.0};

  auto duration =
      std::views::iota(1, 11) | std::views::transform([](int v) -> double {
        return static_cast<double>(v * 100);
      });

  auto func = [&]() -> int {
    for (const double &d : duration) {
      // 模拟轨迹
      auto result = eq.simulate(d, 0.01);
      if (!result) {
        std::println("Simulation failed: {}", result.error().message);
        return 1;
      }
    }
    return 0;
  };

  auto elapsed = timeit(func);
  std::println("Elapsed {}s", elapsed);
  return 0;
}
