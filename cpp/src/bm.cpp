#include "utils.hpp"
import diffusionx.simulation.continuous;

int main() {
    Bm bm{};

    double duration = 100.0;
    double time_step = 0.01;
    size_t num_samples = 10000;

    auto simulate = [&]() {
        auto result = bm.simulate(duration, time_step).value();
    };

    auto msd = [&]() {
        auto result = bm.msd(duration, num_samples, time_step).value();
    };

    bench("Brownian motion simulation", simulate, 10);
    bench("Brownian motion msd", msd, 10);
    return 0;
}
