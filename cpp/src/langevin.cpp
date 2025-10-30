#include <utility>
#include <concepts>
#include <vector>
#include <print>
#include <ranges>
#include "random/normal.hpp"
#include "utils.hpp"

using std::vector;

template<typename T>
concept DoubleParams = std::invocable<T, double, double> &&
    std::same_as<std::invoke_result_t<T, double, double>, double>;

template<DoubleParams F, DoubleParams G>
struct Langevin {
    double starting_position = 0.0;
    F drift;
    G diffusivity;
    Langevin() = default;
    Langevin(F f, G g, double starting_position = 0.0) : drift {f}, diffusivity {g}, starting_position(starting_position) {}

    [[nodiscard]] auto simulate(double duration, double tau = 0.01) const -> std::pair<vector<double>, vector<double>> {
        vector<double> t = linspace(0.0, duration, tau);
        size_t n = t.size() - 1;
        vector<double> x(n+1);
        x[0] = starting_position;
        // auto noise = randn(n).value();
        for (size_t i = 0; i < n; ++i) {
            double mu = drift(x[i], t[i]);
            double D = diffusivity(x[i], t[i]);
            double sigma = std::sqrt(2 * D * tau);
            double noise = rand();
            x[i+1] = x[i] + (mu * tau) + (sigma * noise);
        }
        return std::make_pair(t, x);
    }

    [[nodiscard]] auto msd(double duration, double tau=0.01, size_t particles=10000) const -> double {
        auto simulator = [this, duration, tau]() -> std::pair<vector<double>, vector<double>> {
            return this->simulate(duration, tau);
        };
        return mc_msd(particles, simulator);
    }
};

int main() {
    auto drift = [](double x, double t) -> double {
        return -x;
    };
    auto diffusivity = [](double x, double t) -> double {
        return 1.0;
    };
    Langevin eq {drift, diffusivity};
    auto duration = std::views::iota(1, 11) | std::views::transform([](int v) -> double {
        return static_cast<double>(v * 100);
    });
    auto func = [&]() -> int {
        for(const double& d: duration) {
            double m = eq.msd(d);
        }
        return 0;
    };
    auto elapsed = timeit(func);
    std::println("Elapsed {}s", elapsed);
    return 0;
}
