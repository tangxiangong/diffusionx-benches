#include "random/normal.hpp"
#include "utils.hpp"
#include <print>
#include <ranges>
#include <utility>
#include <vector>

using std::vector;

struct Bm {
  double starting_position = 0.0;
  double diffusivity = 0.5;
  Bm() = default;
  Bm(double starting_position, double diffusivity)
      : starting_position(starting_position), diffusivity(diffusivity) {}

  [[nodiscard]] auto simulate(double duration, double tau = 0.01) const
      -> std::pair<vector<double>, vector<double>> {
    vector<double> t = linspace(0.0, duration, tau);
    size_t n = t.size() - 1;
    vector<double> x(n + 1);
    x[0] = starting_position;
    double sigma = std::sqrt(2 * diffusivity * tau);
    auto noise = randn(n).value();
    for (size_t i = 0; i < n; ++i) {
      x[i + 1] = x[i] + (sigma * noise[i]);
    }
    return std::make_pair(t, x);
  }

  [[nodiscard]] auto msd(double duration, double tau = 0.01,
                         size_t particles = 10000) const -> double {
    auto simulator = [this, duration,
                      tau]() -> std::pair<vector<double>, vector<double>> {
      return this->simulate(duration, tau);
    };
    return mc_moment(particles, 2, simulator);
  }
};

int main() {
  Bm bm{};
  auto duration =
      std::views::iota(1, 11) | std::views::transform([](int v) -> double {
        return static_cast<double>(v * 100);
      });
  auto func = [&]() -> int {
    for (const double &d : duration) {
      double m = bm.msd(d);
    }
    return 0;
  };
  auto elapsed = timeit(func);
  std::println("Elapsed {}s", elapsed);
  return 0;
}
