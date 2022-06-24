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

    glfwSetWindowTitle(window, m_WindowTitle.data());

    if(!gladIsInitialized && !gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Could not initialize glad\n");
    }

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) -> void {
        Window& thisWindow = *((Window*) glfwGetWindowUserPointer(window));
        thisWindow.m_WindowSize = { (size_t) width, (size_t) height};
        glViewport(0, 0, width, height);
    });

    glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
        Window& thisWindow = *((Window*) glfwGetWindowUserPointer(window));
        thisWindow.m_IsOpen = false;
    });

    glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int focused) {
        Window& thisWindow = *((Window*) glfwGetWindowUserPointer(window));
        thisWindow.m_IsFocused = focused;
        if(focused) {
            glViewport(0, 0, thisWindow.m_WindowSize.width, thisWindow.m_WindowSize.height);
        }
    });

    m_IsOpen = true;
}

bool Window::IsOpen() const {
    return m_IsOpen;
}

bool Window::IsFocused() const {
    return m_IsFocused;
}

Size Window::GetSize() const {
    return m_WindowSize;
}

Size Window::GetPosition() const {
    int xPos, yPos;
    glfwGetWindowPos(m_GLFWWindow.get(), &xPos, &yPos);
    return { (size_t) xPos, (size_t) yPos };
}

void Window::Focus() {
    glfwFocusWindow(m_GLFWWindow.get());
}

void Window::RequestFocus() {
    glfwRequestWindowAttention(m_GLFWWindow.get());
}

void Window::Close() {
    m_IsOpen = false;
}

void Window::SetSize(Size newSize) {
    glViewport(0, 0, newSize.width, newSize.height);
    m_WindowSize = newSize;
}

void Window::SetPosition(Size newPos) {
    glfwSetWindowPos(m_GLFWWindow.get(), newPos.width, newPos.height);
}

void Window::MouseCursorVisible(bool visible) {
    glfwSetInputMode(m_GLFWWindow.get(), GLFW_CURSOR_HIDDEN, visible);
}

void Window::WindowVisible(bool visible) {
    glfwSetWindowAttrib(m_GLFWWindow.get(), GLFW_VISIBLE, visible);
}

void Window::SetTitle(std::string_view newTitle) {
    m_WindowTitle = newTitle;
    glfwSetWindowTitle(m_GLFWWindow.get(), newTitle.data());
}

void Window::Clear(Color color) const {
    NormalizedRGB glColor = color.ToNormalizedRGB();
    glClearColor(glColor.r, glColor.g, glColor.b, glColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::Display() const {
    glfwSwapBuffers(m_GLFWWindow.get());
}

}