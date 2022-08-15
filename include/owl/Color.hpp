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

    [[nodiscard]] operator GLRGB() const;
    [[nodiscard]] operator HSV() const;

    static inline const RGB Black() { return {0,   0,   0  }; }
    static inline const RGB White() { return {255, 255, 255}; }
    static inline const RGB Red  () { return {255, 0,   0  }; }
    static inline const RGB Green() { return {0,   255, 0  }; }
    static inline const RGB Blue () { return {0,   0,   255}; }
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

    [[nodiscard]] operator RGB() const;
    [[nodiscard]] operator HSV() const;

    static inline const GLRGB Black() { return {0.f, 0.f, 0.f}; }
    static inline const GLRGB White() { return {1.f, 1.f, 1.f}; }
    static inline const GLRGB Red  () { return {1.f, 0.f, 0.f}; }
    static inline const GLRGB Green() { return {0.f, 1.f, 0.f}; }
    static inline const GLRGB Blue () { return {0.f, 0.f, 1.f}; }
};

struct HSV {
    float h;
    float s;
    float v;

    HSV() = default;
    HSV(const HSV& other) = default;
    HSV(float h, float s, float v) : h(h), s(s), v(v) {}

    [[nodiscard]] operator RGB() const;
    [[nodiscard]] operator GLRGB() const;

    static inline const HSV Black() { return {0.f, 0.f, 0.f}; }
    static inline const HSV White() { return {0.f, 0.f, 1.f}; }
    static inline const HSV Red  () { return {0.f, 1.f, 1.f}; }
    static inline const HSV Green() { return {util::DegToRad(120), 1.f, 1.f}; }
    static inline const HSV Blue () { return {util::DegToRad(240), 0.f, 1.f}; }
};

inline const RGB black(0, 0, 0);
inline const RGB white(255, 255, 255);
inline const RGB red(255, 0, 0);
inline const RGB green(0, 255, 0);
inline const RGB blue(0, 0, 255);

}