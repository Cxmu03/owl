#include <cmath>

#include "Color.hpp"
#include "Util.hpp"

namespace owl::color {

NormalizedRGB RBG::ToNormalizedRGB() const {
    return {
            util::MapToRange(static_cast<float>(r), 0.f, 255.f, 0.f, 1.f),
            util::MapToRange(static_cast<float>(g), 0.f, 255.f, 0.f, 1.f),
            util::MapToRange(static_cast<float>(b), 0.f, 255.f, 0.f, 1.f),
            a
    };
}

HSV RBG::ToHSV() const {
    HSV         out = {0.f, 0.f, 0.f};
    NormalizedRGB normalized = ToNormalizedRGB();
    double      min, max, delta;

    min = normalized.r < normalized.g ? normalized.r : normalized.g;
    min = min  < normalized.b ? min  : normalized.b;

    max = normalized.r > normalized.g ? normalized.r : normalized.g;
    max = max  > normalized.b ? max  : normalized.b;

    out.v = max;                                // v
    delta = max - min;
    if (delta < 0.00001)
    {
        out.s = 0;
        out.h = 0; // undefined, maybe nan?
        return out;
    }
    if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
        out.s = (delta / max);                  // s
    } else {
        // if max is 0, then r = g = b = 0
        // s = 0, h is undefined
        out.s = 0.0;
        out.h = -1.;                            // its now undefined
        return out;
    }
    if( normalized.r >= max )                           // > is bogus, just keeps compilor happy
        out.h = ( normalized.g - normalized.b ) / delta;        // between yellow & magenta
    else
    if( normalized.g >= max )
        out.h = 2.0 + ( normalized.b - normalized.r ) / delta;  // between cyan & yellow
    else
        out.h = 4.0 + ( normalized.r - normalized.g ) / delta;  // between magenta & cyan

    out.h *= 60.0;                              // degrees

    if( out.h < 0.0 )
        out.h += 360.0;

    return out;
}

RBG NormalizedRGB::ToRBG() const {
    return {
            static_cast<uint8_t>(util::MapToRange(r, 0.f, 1.f, 0.f, 255.f)),
            static_cast<uint8_t>(util::MapToRange(g, 0.f, 1.f, 0.f, 255.f)),
            static_cast<uint8_t>(util::MapToRange(b, 0.f, 1.f, 0.f, 255.f)),
            a
    };
}

HSV NormalizedRGB::ToHSV() const {
    return ToRBG().ToHSV();
}

RBG HSV::ToRGB() const {
    return ToNormalizedRGB().ToRBG();
}

NormalizedRGB HSV::ToNormalizedRGB() const {
    NormalizedRGB RGB;
    float H = h, S = s, V = v,
            P, Q, T,
            fract;

    (H == 360.)?(H = 0.):(H /= 60.);
    fract = H - floorf(H);

    P = V*(1.f - S);
    Q = V*(1.f - S*fract);
    T = V*(1.f - S*(1.f - fract));

    if      (0. <= H && H < 1.)
        RGB = {.r = V, .g = T, .b = P};
    else if (1. <= H && H < 2.)
        RGB = {.r = Q, .g = V, .b = P};
    else if (2. <= H && H < 3.)
        RGB = {.r = P, .g = V, .b = T};
    else if (3. <= H && H < 4.)
        RGB = {.r = P, .g = Q, .b = V};
    else if (4. <= H && H < 5.)
        RGB = {.r = T, .g = P, .b = V};
    else if (5. <= H && H < 6.)
        RGB = {.r = V, .g = P, .b = Q};
    else
        RGB = {.r = 0., .g = 0., .b = 0.};

    return RGB;
}

}