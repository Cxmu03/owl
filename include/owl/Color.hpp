#pragma once

#include <stdint.h>

namespace owl::color {

struct NormalizedRGB;
struct HSV;

struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    float a;

    RGB() = default;
    RGB(const RGB& other) = default;
    RGB(uint8_t pr, uint8_t pg, uint8_t pb) : RGB(pr, pg, pb, 1.f) {}
    RGB(uint8_t r, uint8_t g, uint8_t b, float a) : r(r), g(g), b(b), a(1.f) {}

    [[nodiscard]] operator NormalizedRGB() const;
    [[nodiscard]] operator HSV() const;
};

struct NormalizedRGB {
    float r;
    float g;
    float b;
    float a;

    NormalizedRGB() = default;
    NormalizedRGB(const NormalizedRGB& other) = default;
    NormalizedRGB(float pr, float pg, float pb) : NormalizedRGB(pr, pg, pb, 1.f) {}
    NormalizedRGB(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

    [[nodiscard]] operator RGB() const;
    [[nodiscard]] operator HSV() const;
};

struct HSV {
    float h;
    float s;
    float v;

    HSV() = default;
    HSV(const HSV& other) = default;
    HSV(float h, float s, float v) : h(h), s(s), v(v) {}

    [[nodiscard]] operator RGB() const;
    [[nodiscard]] operator NormalizedRGB() const;
};

}