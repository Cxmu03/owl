#include <glad/glad.h>

#include <window.hpp>

namespace owl {

Window::Window(vec2u size, std::string_view title, uint32_t style /* = Default*/) : m_ViewportSize(size), m_WindowTitle(title), m_ClearColor(255, 255, 255) {
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

    GLFWwindow* window = glfwCreateWindow(m_ViewportSize.x, m_ViewportSize.y, title.data(), nullptr, nullptr);
    m_GLFWWindow = std::unique_ptr<GLFWwindow, GlfwWindowDestructor>(window);
    glfwSetWindowUserPointer(window, this);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

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
            glfwMakeContextCurrent(thisWindow.m_GLFWWindow.get());
        }
    });

    SetStyle(style);
    m_CurrentStyle = style;

    m_IsOpen = true;
}

auto PrimaryMonitorSize() -> vec2u {
    const GLFWvidmode* primaryVideoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    return { (unsigned)primaryVideoMode->width, (unsigned)primaryVideoMode->height };
}

auto Window::KeyDown(int key) const -> bool {
    return glfwGetKey(m_GLFWWindow.get(), key) == GLFW_PRESS;
}

auto Window::UpdateViewport() -> void {
    glfwGetFramebufferSize(m_GLFWWindow.get(), (int*)&m_ViewportSize.x, (int*)&m_ViewportSize.y);
    glViewport(0, 0, m_ViewportSize.x, m_ViewportSize.y);
}

auto Window::IsOpen() const -> bool{
    return m_IsOpen;
}

auto Window::IsFocused() const -> bool {
    return m_IsFocused;
}

auto Window::IsFullscreen() const -> bool {
    return glfwGetWindowMonitor(m_GLFWWindow.get()) != nullptr;
}

auto Window::IsMaximized() const -> bool {
    return glfwGetWindowAttrib(m_GLFWWindow.get(), GLFW_MAXIMIZED);
}

auto Window::GetSize() const -> vec2u {
    return m_ViewportSize;
}

auto Window::GetPosition() const -> vec2u {
    int xPos, yPos;
    glfwGetWindowPos(m_GLFWWindow.get(), &xPos, &yPos);
    return { (unsigned) xPos, (unsigned) yPos };
}

auto Window::GetDeltaTime() const -> double {
    return m_DeltaTime;
}

auto Window::Focus() -> void {
    glfwFocusWindow(m_GLFWWindow.get());
}

auto Window::RequestFocus() -> void {
    glfwRequestWindowAttention(m_GLFWWindow.get());
}

auto Window::Close() -> void {
    m_IsOpen = false;
}

auto Window::SetSize(vec2u newSize) -> void {
    glViewport(0, 0, newSize.x, newSize.y);
    m_ViewportSize = newSize;
    m_ViewportSize = newSize;
}

auto Window::ToggleFullscreen() -> void {
    if(IsFullscreen()) {
        glfwSetWindowMonitor(m_GLFWWindow.get(), nullptr, m_WindowPos.x, m_WindowPos.y, m_WindowSizeBuffer.x, m_WindowSizeBuffer.y, GLFW_DONT_CARE);
        UpdateViewport();
        return;
    }
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* vidMode = glfwGetVideoMode(primaryMonitor);
    glfwGetWindowSize(m_GLFWWindow.get(), (int*) &m_WindowSizeBuffer.x, (int*) &m_WindowSizeBuffer.y);
    glfwGetWindowPos(m_GLFWWindow.get(), (int*) &m_WindowPos.x, (int*) &m_WindowPos.y);
    glfwSetWindowMonitor(m_GLFWWindow.get(), primaryMonitor, 0, 0, vidMode->width, vidMode->height, vidMode->refreshRate);
    UpdateViewport();
}

auto Window::Maximize() -> void {
    if(IsMaximized()) {
        return;
    }
    glfwMaximizeWindow(m_GLFWWindow.get());
    UpdateViewport();
}

auto Window::Restore() -> void {
    if(IsMaximized()) {
        glfwRestoreWindow(m_GLFWWindow.get());
        UpdateViewport();
    }
    if(IsFullscreen()) {
        ToggleFullscreen();
    }
}

auto Window::SetStyle(uint32_t style) -> void {
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

auto Window::SetPosition(vec2u newPos) -> void {
    glfwSetWindowPos(m_GLFWWindow.get(), newPos.x, newPos.y);
}

auto Window::MouseCursorVisible(bool visible) -> void {
    glfwSetInputMode(m_GLFWWindow.get(), GLFW_CURSOR_HIDDEN, visible);
}

auto Window::WindowVisible(bool visible) -> void {
    glfwSetWindowAttrib(m_GLFWWindow.get(), GLFW_VISIBLE, visible);
}

auto Window::SetTitle(std::string_view newTitle) -> void {
    m_WindowTitle = newTitle;
    glfwSetWindowTitle(m_GLFWWindow.get(), newTitle.data());
}

auto Window::SetClearColor(color::RGB clearColor) -> void {
    m_ClearColor = clearColor;
}

auto Window::SetVsync(VsyncStatus status) -> void {
    limiter.enabled = status == VsyncStatus::Off;
    GLFWwindow* oldContext = glfwGetCurrentContext(); //Makes sure old context is restored in the use case of multiple windows
    glfwMakeContextCurrent(m_GLFWWindow.get());
    glfwSwapInterval(status == owl::On);
    glfwMakeContextCurrent(oldContext);
}

auto Window::SetFramerateLimit(size_t limit) -> void {
    limiter.SetLimit(limit);
}

auto Window::Clear(color::RGB color) const -> void {
    auto glColor = color::GLRGB(color);
    glClearColor(glColor.r, glColor.g, glColor.b, glColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

auto Window::Clear() const -> void {
    glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

auto Window::Display() const -> void {
    glfwSwapBuffers(m_GLFWWindow.get());
}

}