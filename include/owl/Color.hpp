#ifndef OWL_COLOR_HPP
#define OWL_COLOR_HPP

#include <stdint.h>

namespace owl::color {

struct NormalizedRGB;
struct HSV;

struct RBG {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    float a;

    [[nodiscard]] NormalizedRGB ToNormalizedRGB() const;
    [[nodiscard]] HSV ToHSV() const;
};

struct NormalizedRGB {
    float r;
    float g;
    float b;
    float a;

    [[nodiscard]] RBG ToRBG() const;
    [[nodiscard]] HSV ToHSV() const;
};

struct HSV {
    float h;
    float s;
    float v;

    [[nodiscard]] RBG ToRGB() const;
    [[nodiscard]] NormalizedRGB ToNormalizedRGB() const;
};

}

#endif //OWL_COLOR_HPP
