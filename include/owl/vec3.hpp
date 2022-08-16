#pragma once

#include <cmath>

namespace owl {

template<typename T>
struct vec3 {
    T x, y, z;

    vec3() : vec3(0, 0, 0) {}
    explicit vec3(T v) : vec3(v, v, v) {}
    vec3(T x, T y, T z) : x(x), y(y), z(z) {}
    vec3(const vec3& other) = default;

    auto operator==(const vec3& other) const -> bool = default;

    auto SqrAbs() -> T;
    auto Abs() -> T;
    auto Normalized() -> vec3;
    auto Normalize() -> void;
    auto Negate() -> void;
    auto Multiply(T scalar) -> void;
    auto Add(vec3 other) -> void;
    auto Subtract(vec3 other) -> void;
    auto Dot(vec3 other) -> T;
    auto Cross(vec3 other) -> vec3;

    template<typename O>
    explicit operator vec3<O>();

    auto operator*(T scalar) -> vec3;
    auto operator+(vec3 other) -> vec3;
    auto operator-(vec3 other) -> vec3;
    auto operator-() -> vec3;
};

using vec3f = vec3<float>;
using vec3d = vec3<double>;
using vec3i = vec3<int>;
using vec3l = vec3<long>;
using vec3ll = vec3<long long>;
using vec3c = vec3<char>;
using vec3u = vec3<unsigned>;

template<typename T>
auto vec3<T>::SqrAbs() -> T {
    return x * x + y * y + z * z;
}

template<typename T>
auto vec3<T>::Abs() -> T {
    return std::sqrt(SqrAbs());
};

template<typename T>
auto vec3<T>::Normalized() -> vec3<T> {
    T abs = this->Abs();
    return {x / abs, y / abs, z / abs};
}

template<typename T>
auto vec3<T>::Normalize() -> void {
    T abs = this->Abs();
    x /= abs;
    y /= abs;
    z /= abs;
}

template<typename T>
auto vec3<T>::Negate() -> void {
    z = -z;
    x = -x;
    y = -y;
}

template<typename T>
auto vec3<T>::Multiply(T scalar) -> void {
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

template<typename T>
auto vec3<T>::Add(vec3<T> other) -> void {
    x += other.x;
    y += other.y;
    z += other.z;
}

template<typename T>
auto vec3<T>::Subtract(vec3<T> other) -> void {
    x -= other.x;
    y -= other.y;
    z -= other.z;
}

template<typename T>
auto vec3<T>::Dot(vec3<T> other) -> T {
    return this->x * other.x + this->y * other.y + this->z * other.z;
}

template<typename T>
auto vec3<T>::Cross(vec3<T> other) -> vec3<T> {
    T newX = this->y * other.z - this->z * other.y;
    T newY = this->z * other.x - this->x * other.z;
    T newZ = this->x * other.y - this->y * other.x;
    return {newX, newY, newZ};
}

template<typename T>
template<typename O>
vec3<T>::operator vec3<O>() {
    return {static_cast<O>(x), static_cast<O>(y), static_cast<O>(z)};
}

template<typename T>
auto vec3<T>::operator*(T scalar) -> vec3 {
    return {x * scalar, y * scalar, z * scalar};
}

template<typename T>
auto vec3<T>::operator+(vec3<T> other) -> vec3 {
    return {this->x + other.x, this->y + other.y, this->z + other.z};
}

template<typename T>
auto vec3<T>::operator-(vec3<T> other) -> vec3 {
    return {this->x - other.x, this->y - other.y, this->z - other.z};
}

template<typename T>
auto vec3<T>::operator-() -> vec3 {
    return {-x, -y, -z};
}

}