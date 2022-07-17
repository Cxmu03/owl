#include <glad/glad.h>
#include "../include/owl/Window.hpp"

namespace owl {

Size Size::PrimaryMonitorSize() {
    const GLFWvidmode* primaryVideoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    return { (size_t) primaryVideoMode->width, (size_t) primaryVideoMode->height };
}

bool Window::KeyDown(int key) const {
    return glfwGetKey(m_GLFWWindow.get(), key) == GLFW_PRESS;
}

Window::Window(Size size, std::string_view title, uint32_t style /* = Default*/) : m_ViewportSize(size), m_WindowTitle(title), m_ClearColor(255, 255, 255) {
    static bool glfwIsInitialized;
    static bool gladIsInitialized;

    if(!glfwIsInitialized && !glfwInit()) {
        throw std::runtime_error("Could not initialize glfw\n");
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    if(style & WindowStyle::Maximized) {
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    }

    GLFWwindow* window = glfwCreateWindow(m_ViewportSize.width, m_ViewportSize.height, title.data(), nullptr, nullptr);
    m_GLFWWindow = std::unique_ptr<GLFWwindow, GlfwWindowDestructor>(window);
    glfwSetWindowUserPointer(window, this);
    glfwMakeContextCurrent(window);

    glfwSetWindowTitle(window, m_WindowTitle.data());

    glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);

    if(!gladIsInitialized && !gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Could not initialize glad\n");
    }

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) -> void {
        Window& thisWindow = *((Window*) glfwGetWindowUserPointer(window));
        thisWindow.UpdateViewport();
    });

    glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
        Window& thisWindow = *((Window*) glfwGetWindowUserPointer(window));
        thisWindow.m_IsOpen = false;
        glfwDestroyWindow(thisWindow.m_GLFWWindow.get());
    });

    glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int focused) {
        Window& thisWindow = *((Window*) glfwGetWindowUserPointer(window));
        thisWindow.m_IsFocused = focused;
        if(focused) {
            thisWindow.UpdateViewport();
        }
    });

    SetStyle(style);
    m_CurrentStyle = style;

    m_IsOpen = true;
}

void Window::UpdateViewport() {
    glfwGetFramebufferSize(m_GLFWWindow.get(), (int*)&m_ViewportSize.width, (int*)&m_ViewportSize.height);
    glViewport(0, 0, m_ViewportSize.width, m_ViewportSize.height);
}

bool Window::IsOpen() const {
    return m_IsOpen;
}

bool Window::IsFocused() const {
    return m_IsFocused;
}

bool Window::IsFullscreen() const {
    return glfwGetWindowMonitor(m_GLFWWindow.get()) != nullptr;
}

bool Window::IsMaximized() const {
    return glfwGetWindowAttrib(m_GLFWWindow.get(), GLFW_MAXIMIZED);
}

Size Window::GetSize() const {
    return m_ViewportSize;
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
    m_ViewportSize = newSize;
    m_ViewportSize = newSize;
}

void Window::ToggleFullscreen() {
    if(IsFullscreen()) {
        glfwSetWindowMonitor(m_GLFWWindow.get(), nullptr, m_WindowPos.x, m_WindowPos.y, m_WindowSizeBuffer.width, m_WindowSizeBuffer.height, GLFW_DONT_CARE);
        UpdateViewport();
        return;
    }
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* vidMode = glfwGetVideoMode(primaryMonitor);
    glfwGetWindowSize(m_GLFWWindow.get(), (int*) &m_WindowSizeBuffer.width, (int*) &m_WindowSizeBuffer.height);
    glfwGetWindowPos(m_GLFWWindow.get(), (int*) &m_WindowPos.x, (int*) &m_WindowPos.y);
    glfwSetWindowMonitor(m_GLFWWindow.get(), primaryMonitor, 0, 0, vidMode->width, vidMode->height, vidMode->refreshRate);
    UpdateViewport();
}

void Window::Maxmize() {
    if(IsMaximized()) {
        return;
    }
    glfwMaximizeWindow(m_GLFWWindow.get());
    UpdateViewport();
}

void Window::Restore() {
    if(IsMaximized()) {
        glfwRestoreWindow(m_GLFWWindow.get());
        UpdateViewport();
    }
    if(IsFullscreen()) {
        ToggleFullscreen();
    }
}

void Window::SetStyle(uint32_t style) {
    m_CurrentStyle = style;

    if((!IsFullscreen() && (style & WindowStyle::Fullscreen)) || (IsFullscreen() && !(style & WindowStyle::Fullscreen))) {
        ToggleFullscreen();
        return;
    }

    if(style & WindowStyle::Maximized) {
        glfwSetWindowAttrib(m_GLFWWindow.get(), GLFW_MAXIMIZED, GLFW_TRUE);
    }

    glfwSetWindowAttrib(m_GLFWWindow.get(), GLFW_RESIZABLE, style & WindowStyle::Resize);
    glfwSetWindowAttrib(m_GLFWWindow.get(), GLFW_DECORATED, style & WindowStyle::Decorated);
    glfwSetWindowAttrib(m_GLFWWindow.get(), GLFW_FLOATING, style & WindowStyle::Floating);

    if(style & WindowStyle::Close) {
        glfwSetWindowCloseCallback(m_GLFWWindow.get(), [](GLFWwindow* window) {
            Window& thisWindow = *((Window*) glfwGetWindowUserPointer(window));
            thisWindow.m_IsOpen = false;
            glfwDestroyWindow(thisWindow.m_GLFWWindow.get());
        });
    } else {
        glfwSetWindowCloseCallback(m_GLFWWindow.get(), [](GLFWwindow* window){});
    }
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

void Window::SetClearColor(color::RGB clearColor) {
    m_ClearColor = clearColor;
}

void Window::Clear(color::RGB color) const {
    auto glColor = color::NormalizedRGB(color);
    glClearColor(glColor.r, glColor.g, glColor.b, glColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::Display() const {
    glfwSwapBuffers(m_GLFWWindow.get());
}

}