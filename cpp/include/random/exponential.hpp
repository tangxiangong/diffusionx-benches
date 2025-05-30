#ifndef EXPONENTIAL_HPP
#define EXPONENTIAL_HPP

#include <vector>
#include <format>
#include <type_traits>
#include "../error.hpp"
#include "utils.hpp"

using std::vector;
using std::format;

template<typename T = double> requires std::is_floating_point_v<T>
auto randexp(size_t n, T rate = 1.0) -> Result<vector<T>> {
    if (rate <= 0) {
        return Err(Error::InvalidArgument(format(
            "The rate `rate` must be positive, but got {}",
            rate
        )));
    }
    auto sampler = [rate]() mutable {
        thread_local static std::mt19937 gen = generator();
        std::exponential_distribution<T> dist(rate);
        return dist(gen);
    };
    return Ok(parallel_generate<T>(n, sampler));
}

template<typename T = double> requires std::is_floating_point_v<T>
auto randexp(T rate = 1.0) -> Result<T> {
    if (rate <= 0) {
        return Err(Error::InvalidArgument(format(
            "The rate `rate` must be positive, but got {}",
            rate
        )));
    }

    thread_local static std::mt19937 gen = generator();
    std::exponential_distribution<T> dist(rate);
    return Ok(dist(gen));
}


template<typename T = double> requires std::is_floating_point_v<T>
class Exponential {
    T m_rate = 1.0;

public:
    Exponential() = default;

    explicit Exponential(T rate) : m_rate(rate) {
        if (m_rate <= 0) {
            throw std::invalid_argument(format(
                "The rate parameter `rate` must be positive, but got {}",
                m_rate
            ));
        }
    }

    [[nodiscard]] auto get_rate() const -> T {
        return m_rate;
    }

    [[nodiscard]] auto sample(size_t n) const -> Result<vector<T>> {
        return randexp(n, m_rate);
    }
};

#endif //EXPONENTIAL_HPP
