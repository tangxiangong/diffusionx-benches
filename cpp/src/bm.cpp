#include "utils.hpp"
#include <print>
#include <ranges>
#include <vector>

import diffusionx.simulation.continuous;

using std::vector;

int main() {
  // 创建布朗运动：起始位置 0.0，扩散系数 0.5
  Bm bm{};

  auto duration =
      std::views::iota(1, 11) | std::views::transform([](int v) -> double {
        return static_cast<double>(v * 100);
      });

  auto func = [&]() -> int {
    for (const double &d : duration) {
      // 模拟轨迹
      auto result = bm.msd(d, 10000, 0.01);
      if (!result) {
        return 1;
      }
    }
    return 0;
  };

  auto elapsed = timeit(func);
  std::println("Elapsed {}s", elapsed);
  return 0;
}
