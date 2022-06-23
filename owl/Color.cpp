#include "Color.hpp"
#include "Util.hpp"

namespace owl {

GlColor Color::ToGlColor() {
    return {
        MapToRange(static_cast<float>(r), 0.f, 255.f, 0.f, 1.f),
        MapToRange(static_cast<float>(g), 0.f, 255.f, 0.f, 1.f),
        MapToRange(static_cast<float>(b), 0.f, 255.f, 0.f, 1.f),
        a
    };
}

Color GlColor::ToRBG() {
    return {
        static_cast<uint8_t>(MapToRange(r, 0.f, 1.f, 0.f, 255.f)),
        static_cast<uint8_t>(MapToRange(r, 0.f, 1.f, 0.f, 255.f)),
        static_cast<uint8_t>(MapToRange(r, 0.f, 1.f, 0.f, 255.f)),
        a
    };
}

}