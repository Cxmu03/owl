#ifndef OWL_WINDOW_HPP
#define OWL_WINDOW_HPP

#include <memory>
#include <string_view>
#include <functional>

#include <GLFW/glfw3.h>

#include "Color.hpp"

namespace owl {

struct Size {
    size_t width;
    size_t height;

    static Size PrimaryMonitorSize();
};

enum WindowStyle {
    Resize = 1 << 0,
    Decorated = 1 << 1,
    Fullscreen = 1 << 2,
    Floating = 1 << 3,
    Default = Resize | Decorated
};

class Window {
public:
    Window(Size size, std::string_view title, WindowStyle style = Default);

public:
    //void Run(const std::function<void(Window&)>& updateFunc);
    template <typename UpdateFunc>
    void Run(UpdateFunc fun);

    [[nodiscard]] bool IsOpen() const;
    void Close();

    void Clear(Color);
    void Display();

private:
    struct GlfwWindowDestructor {
        void operator()(GLFWwindow* window) {
            glfwDestroyWindow(window);
        }
    };

private:
    std::unique_ptr<GLFWwindow, GlfwWindowDestructor> m_GLFWWindow;
    std::string_view m_WindowTitle;
    owl::Size m_WindowSize;
    bool isOpen;
};

template <typename UpdateFunc>
void Window::Run(UpdateFunc fun) {
    while(this->isOpen) {
        this->Clear({255, 255, 255, 1.f});
        fun();
        this->Display();
        glfwPollEvents();
    }
}

}

#endif //OWL_WINDOW_HPP
