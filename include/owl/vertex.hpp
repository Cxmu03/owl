#pragma once

#include "vec3.hpp"
#include "vec2.hpp"
#include "color.hpp"

namespace owl {

struct Vertex {
    vec3f pos;
    color::GLRGB color;
    vec2f texCoords;

    Vertex() : Vertex(vec3f(0.f, 0.f, 0.f)) {}
    explicit Vertex(vec3f pos) : Vertex(pos, color::GLRGB::Black()) {}
    Vertex(vec3f pos, color::GLRGB color) : Vertex(pos, color, vec2f(0.f, 0.f)) {}
    Vertex(vec3f pos, color::GLRGB color, vec2f texCoords) : pos(pos), color(color), texCoords(texCoords) {}
    Vertex(const Vertex& other) = default;
};

}