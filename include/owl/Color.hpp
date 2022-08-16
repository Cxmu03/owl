#pragma once

#include <stdint.h>

#include "Util.hpp"

namespace owl::color {

struct GLRGB;
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

    auto operator ==(const RGB& other) const -> bool = default;

    [[nodiscard]] operator GLRGB() const;
    [[nodiscard]] operator HSV() const;

    static inline auto Black() -> RGB { return {0,   0,   0  }; }
    static inline auto White() -> RGB { return {255, 255, 255}; }
    static inline auto Red  () -> RGB { return {255, 0,   0  }; }
    static inline auto Green() -> RGB { return {0,   255, 0  }; }
    static inline auto Blue () -> RGB { return {0,   0,   255}; }
};

struct GLRGB {
    float r;
    float g;
    float b;
    float a;

    GLRGB() = default;
    GLRGB(const GLRGB& other) = default;
    GLRGB(float pr, float pg, float pb) : GLRGB(pr, pg, pb, 1.f) {}
    GLRGB(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

    auto operator ==(const GLRGB& other) const -> bool = default;

    [[nodiscard]] operator RGB() const;
    [[nodiscard]] operator HSV() const;

    static inline auto Black() -> GLRGB { return {0.f, 0.f, 0.f}; }
    static inline auto White() -> GLRGB { return {1.f, 1.f, 1.f}; }
    static inline auto Red  () -> GLRGB { return {1.f, 0.f, 0.f}; }
    static inline auto Green() -> GLRGB { return {0.f, 1.f, 0.f}; }
    static inline auto Blue () -> GLRGB { return {0.f, 0.f, 1.f}; }
};

struct HSV {
    float h;
    float s;
    float v;

    HSV() = default;
    HSV(const HSV& other) = default;
    HSV(float h, float s, float v) : h(h), s(s), v(v) {}

    auto operator ==(const HSV& other) const -> bool = default;

    [[nodiscard]] operator RGB() const;
    [[nodiscard]] operator GLRGB() const;

    static inline auto Black() -> HSV { return {0.f, 0.f, 0.f}; }
    static inline auto White() -> HSV { return {0.f, 0.f, 1.f}; }
    static inline auto Red  () -> HSV { return {0.f, 1.f, 1.f}; }
    static inline auto Green() -> HSV { return {util::DegToRad(120), 1.f, 1.f}; }
    static inline auto Blue () -> HSV { return {util::DegToRad(240), 0.f, 1.f}; }
};

}