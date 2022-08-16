#pragma once

#include <memory>
#include <string_view>
#include <functional>

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include "Color.hpp"
#include "FpsUtils.hpp"

namespace owl {

struct Size {
    size_t width;
    size_t height;

    static auto PrimaryMonitorSize() -> Size;
};

enum VsyncStatus {
    On = 0,
    Off
};

enum WindowStyle {
    Resize = 1 << 0,
    Decorated = 1 << 1,
    Close = 1 << 2,
    Fullscreen = 1 << 3,
    Floating = 1 << 4,
    Maximized = 1 << 5,
    Default = Resize | Decorated | Close
};

class Window {
public:
    Window(Size size, std::string_view title, uint32_t style = WindowStyle::Default);

public:
    template<typename UpdateFunc>
    auto Run(UpdateFunc fun) -> void;

    template<typename UpdateFunc>
    auto RunRaw(UpdateFunc fun) -> void;

    [[nodiscard]] auto IsOpen() const -> bool;
    [[nodiscard]] auto IsFocused() const -> bool;
    [[nodiscard]] auto IsFullscreen() const -> bool;
    [[nodiscard]] auto IsMaximized() const -> bool;
    [[nodiscard]] auto KeyDown(int) const -> bool;
    [[nodiscard]] auto GetSize() const -> Size;
    [[nodiscard]] auto GetPosition() const -> Size;
    [[nodiscard]] auto GetDeltaTime() const -> double;

    auto SetTitle(std::string_view) -> void;
    auto SetSize(Size) -> void;
    auto SetStyle(uint32_t) -> void;
    auto SetClearColor(color::RGB) -> void;
    auto SetVsync(VsyncStatus) -> void;
    auto SetFramerateLimit(size_t) -> void;
    auto ToggleFullscreen() -> void;
    auto Maximize() -> void;
    auto Restore() -> void;
    auto WindowVisible(bool) -> void;
    auto SetPosition(Size) -> void;
    auto MouseCursorVisible(bool) -> void;
    auto Focus() -> void;
    auto RequestFocus() -> void;

    auto Close() -> void;

    auto Clear() const -> void;
    auto Clear(color::RGB) const -> void;
    auto Display() const -> void;

private:
    auto UpdateViewport() -> void;

private:
    struct GlfwWindowDestructor {
        auto operator()(GLFWwindow* window) -> void {
            glfwDestroyWindow(window);
        }
    };

private:
    std::unique_ptr<GLFWwindow, GlfwWindowDestructor> m_GLFWWindow;
    std::string_view m_WindowTitle;
    color::GLRGB m_ClearColor;
    Size m_ViewportSize;
    Size m_WindowSizeBuffer;
    glm::vec<2, size_t> m_WindowPos;
    bool m_IsOpen;
    bool m_IsFocused;
    double m_DeltaTime;
    FramerateLimiter limiter;
    uint32_t m_CurrentStyle;
};

template<typename UpdateFunc>
auto Window::Run(UpdateFunc fun) -> void {
    while (this->m_IsOpen) {
        m_DeltaTime = limiter.NextFrame();
        this->Clear();
        this->Clear(m_ClearColor);
        fun();
        this->Display();
        glfwPollEvents();
    }
}

template<typename UpdateFunc>
auto Window::RunRaw(UpdateFunc fun) -> void {
    while (this->m_IsOpen) {
        m_DeltaTime = limiter.NextFrame();
        fun();
    }
}

}