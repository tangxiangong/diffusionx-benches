#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>
#include <expected>
#include <optional>
#include <utility>

struct Error {
    std::string message;

    explicit Error(std::string msg) : message(std::move(msg)) {
    }

    static auto InvalidArgument(const std::string &msg) -> Error {
        return Error("Invalid argument: " + msg);
    }
};

template<typename T>
using Result = std::expected<T, Error>;

inline auto Err(const Error &e) -> std::unexpected<Error> {
    return std::unexpected<Error>(e);
}

template<typename T>
auto Ok(T &&value) -> std::expected<T, Error> {
    return std::expected<T, Error>(std::forward<T>(value));
}

template<typename T>
auto Some(T &&value) -> std::optional<T> {
    return std::optional<T>(std::forward<T>(value));
}

using None = std::nullopt_t;

template<typename T>
auto unwrap(const Result<T> &result) -> T {
    return *result;
}

#endif //ERROR_HPP
