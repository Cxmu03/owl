#ifndef OWL_COLOR_HPP
#define OWL_COLOR_HPP

#include <stdint.h>

namespace owl {

struct NormalizedRGB;
struct HSV;

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    float a;

    NormalizedRGB ToNormalizedRGB();
    HSV ToHSV();
};

struct NormalizedRGB {
    float r;
    float g;
    float b;
    float a;

    Color ToRBG();
    HSV ToHSV();
};

struct HSV {
    float h;
    float s;
    float l;
    float v;

    Color ToRGB();
    NormalizedRGB ToNormalizedRGB();
};

}

#endif //OWL_COLOR_HPP
