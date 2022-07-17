#include "../../owl/Window.hpp"
#include "../../owl/Shader.hpp"
#include "../../owl/Color.hpp"

#include "glad/glad.h"

std::vector<float> vertices = {
        -0.5f, -0.5f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f,
         0.f,   0.5f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f,
         0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f,
};

int main() {
    owl::Window window({500, 500}, "Poggers");

    unsigned vbo, vao;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindVertexArray(vao);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);

    owl::Shader shader({
        owl::VertexShader("../example/shader.vert"),
        owl::FragmentShader("../example/shader.frag")
    });
    shader.SetVertexAttributes(VertexAttribute<int>(), VertexAttribute<float>());
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*) (3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*) (6 * sizeof(GL_FLOAT)));

    window.RunRaw([&](){
        window.Clear({255, 0, 0, 1.f});
        shader.Use();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        window.Display();
        glfwPollEvents();
    });
}