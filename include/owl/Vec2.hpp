#pragma once

#include <cmath>

namespace owl {

template <typename T>
struct Vec2 {
    T x;
    T y;

    T Dot(Vec2 other) const;
    Vec2 Normalized() const;
    Vec2 Rotated(float angle) const;
    Vec2 ScalarMul(T scalar) const;

    T Length() const;

    void Normalize();
    void Rotate(float angle);

    float AngleBetween(Vec2 other) const;

    Vec2 operator +(Vec2 other) const;
    Vec2 operator -(Vec2 other) const;
    Vec2 operator -() const;
    T operator *(Vec2 other) const;
    Vec2 operator *(T scalar) const;
};

template <typename T>
T Vec2<T>::Length() const {
    return std::sqrt(x * x + y * y);
}

template <typename T>
T Vec2<T>::Dot(Vec2<T> other) const {
    return x * other.x + y * other.y;
}
template <typename T>
Vec2<T> Vec2<T>::Normalized() const {
    T len = Length();
    return { x / len, y / len };
}

template <typename T>
Vec2<T> Vec2<T>::Rotated(float angle) const {
    return { x * std::cos(angle) - y * std::cos(angle), x * std::sin(angle) + y * std::cos(angle) };
}

template <typename T>
Vec2<T> Vec2<T>::ScalarMul(T scalar) const {
    return {x * scalar, y * scalar};
}

template <typename T>
Vec2<T> Vec2<T>::operator +(Vec2<T> other) const {
    return { x + other.x, y + other.y };
}

template <typename T>
T Vec2<T>::operator *(Vec2<T> other) const {
    return Dot(other);
}

template <typename T>
Vec2<T> Vec2<T>::operator *(T scalar) const {
    return ScalarMul(scalar);
}

template <typename T>
Vec2<T> Vec2<T>::operator -(Vec2<T> other) const {
    return { x - other.x, y - other.y };
}

template <typename T>
Vec2<T> Vec2<T>::operator -() const {
    return { -x, -y };
}

template <typename T>
void Vec2<T>::Normalize() {
    *this = Normalized();
}

template <typename T>
void Vec2<T>::Rotate(float angle) {
    *this = Rotated(angle);
}

template <typename T>
float Vec2<T>::AngleBetween(Vec2<T> other) const {
    return std::acos((this->Dot(other)) / (this->Length() * other.Length()));
}

using Vec2c = Vec2<uint8_t>;
using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;
using Vec2u = Vec2<size_t>;

}