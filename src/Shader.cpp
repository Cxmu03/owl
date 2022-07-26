#include <vector>

#include <glad/glad.h>

#include <Shader.hpp>
#include "Util.hpp"

struct ShaderSourceHelper {
    const char* data;
    explicit ShaderSourceHelper(std::string_view s) : data(s.data()) {}
    operator const char**() { return &data; };
};

namespace owl {

ShaderInfo GeometryShader(std::string content) {
    return { ShaderType::GeometryShader, std::move(content) };
}

ShaderInfo VertexShader(std::string content) {
    return { ShaderType::VertexShader, std::move(content) };
}

ShaderInfo FragmentShader(std::string content) {
    return { ShaderType::FragmentShader, std::move(content) };
}

Shader::Shader() : m_ProgramId(glCreateProgram()) {}

Shader::Shader(std::initializer_list<ShaderInfo> shaderInfos, ShaderFrom shaderFrom /*= ShaderFrom::File */) : m_ProgramId(glCreateProgram()) {
    Create(shaderInfos, shaderFrom);
}

void Shader::Create(std::initializer_list<ShaderInfo> shaderInfos, ShaderFrom shaderFrom /*= ShaderFrom::File */) {
    m_ProgramId = glCreateProgram();
    int success;
    int logLength;
    std::vector<unsigned> shadersToDelete;

    for (const auto &shaderInfo: shaderInfos) {
        std::string shaderSource = util::ReadFromFile(shaderInfo.content);
        unsigned shaderID = glCreateShader((GLenum) shaderInfo.type);
        shadersToDelete.emplace_back(shaderID);
        std::string shaderCode = (shaderFrom == ShaderFrom::File) ? util::ReadFromFile(shaderInfo.content) : shaderInfo.content;
        glShaderSource(shaderID, 1, ShaderSourceHelper(shaderCode), nullptr);
        glCompileShader(shaderID);
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
            std::string infoLog(logLength, '\0');
            glGetShaderInfoLog(shaderID, logLength, nullptr, &infoLog[0]);
            DeleteShaders(shadersToDelete);
            std::stringstream errorMessage;
            errorMessage << "Could not compile shader:\n" << shaderInfo.content << "\n\nError message:" << infoLog << "\n";
            throw std::runtime_error(errorMessage.str());
        }

        glAttachShader(m_ProgramId, shaderID);
    }

    glLinkProgram(m_ProgramId);
    glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramiv(m_ProgramId, GL_INFO_LOG_LENGTH, &logLength);
        std::string infoLog(logLength, '\0');
        glGetProgramInfoLog(m_ProgramId, logLength, nullptr, &infoLog[0]);
        std::stringstream errorMessage;
        DeleteShaders(shadersToDelete);
        errorMessage << "Could not link program:\n" << "Error message:" << infoLog << "\n";
        throw std::runtime_error(errorMessage.str());
    }

    DeleteShaders(shadersToDelete);
}

void Shader::Use() const {
    glUseProgram(m_ProgramId);
}

void Shader::DeleteShaders(const std::vector<unsigned int> &shaders) const {
    for(const auto shader : shaders) {
        glDetachShader(m_ProgramId, shader);
        glDeleteShader(shader);
    }
}

Shader::~Shader() {
    glDeleteProgram(m_ProgramId);
}
}