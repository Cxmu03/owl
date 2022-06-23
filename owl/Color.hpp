#ifndef OWL_COLOR_HPP
#define OWL_COLOR_HPP

#include <stdint.h>

namespace owl {

struct GlColor;

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    float a;

    GlColor ToGlColor();
};

struct GlColor {
    float r;
    float g;
    float b;
    float a;

    Color ToRBG();
};

}

#endif //OWL_COLOR_HPP
