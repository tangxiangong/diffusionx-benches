#ifndef GAMMA_HPP
#define GAMMA_HPP

#include <vector>
#include <format>
#include <type_traits>

#include "../error.hpp"
#include "utils.hpp"

using std::vector;
using std::format;

template<typename T = double> requires std::is_floating_point_v<T>
auto rand_gamma(size_t n, T shape, T scale) -> Result<vector<T>> {
    if (shape <= 0) {
        return Err(Error::InvalidArgument(format(
            "The shape parameter `shape` must be positive, but got {}",
            shape
        )));
    }

    if (scale <= 0) {
        return Err(Error::InvalidArgument(format(
            "The scale parameter `scale` must be positive, but got {}",
            scale
        )));
    }

    auto sampler = [shape, scale]() mutable {
        thread_local static std::mt19937 gen = generator();
        std::gamma_distribution<T> dist(shape, scale);
        return dist(gen);
    };
    return Ok(parallel_generate<T>(n, sampler));
}

template<typename T = double> requires std::is_floating_point_v<T>
auto rand_gamma(T shape, T scale) -> Result<vector<T>> {
    if (shape <= 0) {
        return Err(Error::InvalidArgument(format(
            "The shape parameter `shape` must be positive, but got {}",
            shape
        )));
    }

    if (scale <= 0) {
        return Err(Error::InvalidArgument(format(
            "The scale parameter `scale` must be positive, but got {}",
            scale
        )));
    }


    thread_local static std::mt19937 gen = generator();
    std::gamma_distribution<T> dist(shape, scale);
    return Ok(dist(gen));
}


template<typename T = double> requires std::is_floating_point_v<T>
class Gamma {
    T m_shape;
    T m_scale;

public:
    Gamma() = default;

    Gamma(T shape, T scale) : m_shape(shape), m_scale(scale) {
        if (m_shape <= 0) {
            throw std::invalid_argument(format(
                "The shape parameter `shape` must be positive, but got {}",
                m_shape
            ));
        }

        if (m_scale <= 0) {
            throw std::invalid_argument(format(
                "The scale parameter `scale` must be positive, but got {}",
                m_scale
            ));
        }
    }

    [[nodiscard]] auto get_shape() const -> T {
        return m_shape;
    }

    [[nodiscard]] auto get_scale() const -> T {
        return m_scale;
    }

    [[nodiscard]] auto sample(size_t n) const -> Result<vector<T>> {
        return rand_gamma(n, m_shape, m_scale);
    }
};


#endif //GAMMA_HPP
