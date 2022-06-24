#include "Color.hpp"
#include "Util.hpp"

namespace owl {

NormalizedRGB Color::ToNormalizedRGB() {
    return {
            MapToRange(static_cast<float>(r), 0.f, 255.f, 0.f, 1.f),
            MapToRange(static_cast<float>(g), 0.f, 255.f, 0.f, 1.f),
            MapToRange(static_cast<float>(b), 0.f, 255.f, 0.f, 1.f),
            a
    };
}

HSV Color::ToHSV() {
    HSV         out;
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

Color NormalizedRGB::ToRBG() {
    return {
            static_cast<uint8_t>(MapToRange(r, 0.f, 1.f, 0.f, 255.f)),
            static_cast<uint8_t>(MapToRange(r, 0.f, 1.f, 0.f, 255.f)),
            static_cast<uint8_t>(MapToRange(r, 0.f, 1.f, 0.f, 255.f)),
            a
    };
}

HSV NormalizedRGB::ToHSV() {
    return ToRBG().ToHSV();
}

Color HSV::ToRGB() {
    return ToNormalizedRGB().ToRBG();
}

NormalizedRGB HSV::ToNormalizedRGB() {
    double      hh, p, q, t, ff;
    long        i;

    NormalizedRGB out;

    if(s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = v;
        out.g = v;
        out.b = v;
        return out;
    }
    hh = h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = v * (1.0 - s);
    q = v * (1.0 - (s * ff));
    t = v * (1.0 - (s * (1.0 - ff)));

    switch(i) {
    case 0:
        out.r = v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = v;
        break;
    case 5:
    default:
        out.r = v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;
}

}