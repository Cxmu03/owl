#ifndef OWL_VEC2_HPP
#define OWL_VEC2_HPP

namespace owl {

template <typename T>
struct Vec2 {
    T x;
    T y;
};

using Vec2c = Vec2<uint8_t>;
using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;
using Vec2u = Vec2<size_t>;

}

#endif //OWL_VEC2_HPP
