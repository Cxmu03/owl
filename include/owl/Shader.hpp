#pragma once

#include <string_view>
#include <string>
#include <iostream>
#include <vector>

#include <glad/glad.h>

namespace owl {

constexpr static const char* s_DefaultVertexShader =
        "#version 330 core\n"
        "layout (location=0) vec3 vertexPosition;\n"
        "layout (location=1) vec3 vertexColor;\n"
        "layout (location=2) vec2 vertexTexCoords;\n"
        "out vec3 vColor;\n"
        "out vec3 vTexCoords;\n"
        "void main() {\n"
        "   gl_Position = vec4(vertexPosition, 1.0);\n"
        "   vColor = vertexColor;\n"
        "   vTexCoords = vertexTexCoords;\n"
        "}\n";

enum class ShaderFrom {
    File,
    Source
};

enum class ShaderType {
    VertexShader   = GL_VERTEX_SHADER,
    GeometryShader = GL_GEOMETRY_SHADER,
    FragmentShader = GL_FRAGMENT_SHADER
};

struct ShaderInfo {
    ShaderType type;
    std::string content;
};

auto GeometryShader(std::string content) -> ShaderInfo;
auto VertexShader(std::string content) -> ShaderInfo;
auto FragmentShader(std::string content) -> ShaderInfo;

class Shader {
public:
    Shader();
    Shader(std::initializer_list<ShaderInfo> shaderInfos, ShaderFrom shaderFrom = ShaderFrom::File);
    Shader(const Shader &other) = default;
    ~Shader();

public:
    auto Create(std::initializer_list<ShaderInfo> shaderInfos, ShaderFrom shaderFrom = ShaderFrom::File) -> void;
    auto Use() const -> void;

private:
    auto DeleteShaders(const std::vector<unsigned>& shaders) const -> void;

private:
    unsigned m_ProgramId;
};

}