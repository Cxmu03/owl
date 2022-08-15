#pragma once

#pragma once

#include <cmath>

namespace owl {

template<typename T>
struct vec2 {
    T x, y;

    auto SqrAbs() -> T;
    auto Abs() -> T;
    auto Normalized() -> vec2;
    auto Normalize() -> void;
    auto Negate() -> void;
    auto Multiply(T scalar) -> void;
    auto Add(vec2 other) -> void;
    auto Subtract(vec2 other) -> void;
    auto Dot(vec2 other) -> T;

    template<typename O>
    explicit operator vec2<O>();

    auto operator*(T scalar) -> vec2;
    auto operator+(vec2 other) -> vec2;
    auto operator-(vec2 other) -> vec2;
    auto operator-() -> vec2;
};

using vec2f = vec2<float>;
using vec2d = vec2<double>;
using vec2i = vec2<int>;
using vec2l = vec2<long>;
using vec2ll = vec2<long long>;
using vec2c = vec2<char>;
using vec2u = vec2<unsigned>;

template<typename T>
auto vec2<T>::SqrAbs() -> T {
    return x * x + y * y;
}

template<typename T>
auto vec2<T>::Abs() -> T {
    return std::sqrt(SqrAbs());
};

template<typename T>
auto vec2<T>::Normalized() -> vec2<T> {
    T abs = this->Abs();
    return {x / abs, y / abs};
}

template<typename T>
auto vec2<T>::Normalize() -> void {
    T abs = this->Abs();
    x /= abs;
    y /= abs;
}

template<typename T>
auto vec2<T>::Negate() -> void {
    x = -x;
    y = -y;
}

template<typename T>
auto vec2<T>::Multiply(T scalar) -> void {
    x *= scalar;
    y *= scalar;
}

template<typename T>
auto vec2<T>::Add(vec2<T> other) -> void {
    x += other.x;
    y += other.y;
}

template<typename T>
auto vec2<T>::Subtract(vec2<T> other) -> void {
    x -= other.x;
    y -= other.y;
}

template<typename T>
auto vec2<T>::Dot(vec2<T> other) -> T {
    return this->x * other.x + this->y * other.y;
}

template<typename T>
template<typename O>
vec2<T>::operator vec2<O>() {
    return {static_cast<O>(x), static_cast<O>(y)};
}

template<typename T>
auto vec2<T>::operator*(T scalar) -> vec2 {
    return {x * scalar, y * scalar};
}

template<typename T>
auto vec2<T>::operator+(vec2<T> other) -> vec2 {
    return {this->x + other.x, this->y + other.y};
}

template<typename T>
auto vec2<T>::operator-(vec2<T> other) -> vec2 {
    return {this->x - other.x, this->y - other.y};
}

template<typename T>
auto vec2<T>::operator-() -> vec2 {
    return {-x, -y};
}

}