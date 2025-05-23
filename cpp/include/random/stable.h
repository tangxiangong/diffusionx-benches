#ifndef STABLE_H
#define STABLE_H
#include <vector>
#include <format>
#include "../error.hpp"


using std::vector;
using std::format;

auto rand_stable(double alpha, double beta = 0.0, double sigma = 1.0, double mu = 0.0) -> Result<double>;

auto rand_stable(size_t n, double alpha, double beta = 0.0,
                                    double sigma = 1.0, double mu = 0.0) -> Result<vector<double>>;

auto rand_skew_stable(double alpha) -> Result<double>;

auto rand_skew_stable(size_t n, double alpha) -> Result<vector<double>>;

class Stable {
    double m_alpha;
    double m_beta;
    double m_sigma;
    double m_mu;

public:
    Stable() = default;

    explicit Stable(double alpha, double beta = 0.0, double sigma = 1.0, double mu = 0.0);

    [[nodiscard]] auto get_alpha() const -> double;

    [[nodiscard]] auto get_beta() const -> double;

    [[nodiscard]] auto get_sigma() const -> double;

    [[nodiscard]] auto get_mu() const -> double;

    [[nodiscard]] auto sample(size_t n) const -> Result<vector<double>>;
};
#endif //STABLE_H
