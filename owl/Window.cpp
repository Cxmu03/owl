#include <glad/glad.h>

#include "Window.hpp"

namespace owl {

Size Size::PrimaryMonitorSize() {
    const GLFWvidmode* primaryVideoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    return { (size_t) primaryVideoMode->width, (size_t) primaryVideoMode->height };
}

Window::Window(Size size, std::string_view title, WindowStyle style /* = Default*/) : m_WindowSize(size), m_WindowTitle(title) {
    static bool glfwIsInitialized;
    static bool gladIsInitialized;

    if(!glfwIsInitialized && !glfwInit()) {
        throw std::runtime_error("Could not initialize glfw\n");
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(m_WindowSize.width, m_WindowSize.height, title.data(), nullptr, nullptr);
    m_GLFWWindow = std::unique_ptr<GLFWwindow, GlfwWindowDestructor>(window);
    glfwSetWindowUserPointer(window, this);
    glfwMakeContextCurrent(window);

    if(!gladIsInitialized && !gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Could not initialize glad\n");
    }

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) -> void {
        Window& thisWindow = *((Window*) glfwGetWindowUserPointer(window));
        thisWindow.m_WindowSize = { (size_t) width, (size_t) height};
    });

    glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
        Window& thisWindow = *((Window*) glfwGetWindowUserPointer(window));
        thisWindow.isOpen = false;
    });

    isOpen = true;
}

bool Window::IsOpen() const {
    return isOpen;
}

void Window::Close() {
    isOpen = false;
}

void Window::Clear(Color color) {
    GlColor glColor = color.ToGlColor();
    glClearColor(glColor.r, glColor.g, glColor.b, glColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::Display() {
    glfwSwapBuffers(m_GLFWWindow.get());
}

}