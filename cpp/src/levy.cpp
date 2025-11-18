#include "utils.hpp"
#include <print>
#include <ranges>
#include <vector>

import diffusionx.simulation.continuous;

using std::vector;

int main() {
  // 创建 Levy 过程：alpha=0.7, beta=0, sigma=1, mu=0, start_position=0
  Levy levy{0.7, 0.0, 1.0, 0.0, 0.0};

  auto duration =
      std::views::iota(1, 11) | std::views::transform([](int v) -> double {
        return static_cast<double>(v * 100);
      });

  auto func = [&]() -> int {
    for (const double &d : duration) {
      // 模拟轨迹
      auto result = levy.simulate(d, 0.01);
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
