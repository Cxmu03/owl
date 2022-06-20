#ifndef OWL_WINDOW_H
#define OWL_WINDOW_H

#include <memory>

#include <GLFW/glfw3.h>

namespace owl {

class Window {
public:

private:
    std::unique_ptr<GLFWwindow> m_GLFWWindow;
    std::pair<size_t, size_t> m_WindowSize;
};

}

#endif //OWL_WINDOW_H
