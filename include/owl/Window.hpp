#ifndef OWL_WINDOW_HPP
#define OWL_WINDOW_HPP

#include <memory>
#include <string_view>
#include <functional>

#include "GLFW/glfw3.h"

#include "Color.hpp"
#include "Vec2.hpp"

namespace owl {

struct Size {
    size_t width;
    size_t height;

    static Size PrimaryMonitorSize();
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
    void Run(UpdateFunc fun);

    template<typename UpdateFunc>
    void RunRaw(UpdateFunc fun);

    [[nodiscard]] bool IsOpen() const;
    [[nodiscard]] bool IsFocused() const;
    [[nodiscard]] bool IsFullscreen() const;
    [[nodiscard]] bool IsMaximized() const;
    [[nodiscard]] bool KeyDown(int) const;
    [[nodiscard]] Size GetSize() const;
    [[nodiscard]] Size GetPosition() const;

    void SetTitle(std::string_view);
    void SetSize(Size);
    void SetStyle(uint32_t);
    void SetClearColor(color::RGB);
    void ToggleFullscreen();
    void Maxmize();
    void Restore();
    void WindowVisible(bool);
    void SetPosition(Size);
    void MouseCursorVisible(bool);
    void Focus();
    void RequestFocus();

    void Close();

    void Clear(color::RGB) const;
    void Display() const;

private:
    void UpdateViewport();
    void PushState();
    void PopState();

private:
    struct GlfwWindowDestructor {
        void operator()(GLFWwindow* window) {
            glfwDestroyWindow(window);
        }
    };

private:
    std::unique_ptr<GLFWwindow, GlfwWindowDestructor> m_GLFWWindow;
    std::string_view m_WindowTitle;
    color::RGB m_ClearColor;
    Size m_ViewportSize;
    Size m_WindowSizeBuffer;
    Vec2u m_WindowPos;
    bool m_IsOpen;
    bool m_IsFocused;
    uint32_t m_CurrentStyle;
};

template<typename UpdateFunc>
void Window::Run(UpdateFunc fun) {
    while (this->m_IsOpen) {
        this->Clear(m_ClearColor);
        fun();
        this->Display();
        glfwWaitEvents();
    }
}

template<typename UpdateFunc>
void Window::RunRaw(UpdateFunc fun) {
    while (this->m_IsOpen) {
        fun();
    }
}

}

#endif //OWL_WINDOW_HPP
