// clang-format off
#define GLEW_STATIC
#include "GL/glew.h"
// clang-format on

#include "Dawn/Window.h"

#include "Dawn/Log.h"

namespace Dawn
{
    bool Window::initialized = false;

    Window::Window(int width, int height, const char* name)
    {
        if (!Window::initialized) {
            if (glfwInit() == GLFW_FALSE) {
                LOG("Failed to initialize GLFW");
            }
        }
        // Create GLFW Window
        m_window = glfwCreateWindow(width, height, name, NULL, NULL);
        if (m_window == NULL) {
            LOG("Failed to create GLFW window");
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(m_window);

        if (!Window::initialized) {
            // Initialize GLEW
            GLenum err = glewInit();
            if (GLEW_OK != err) {
                LOG("Failed to initialize GLEW");
                return;
            }
        }

        glViewport(0, 0, width, height);

        Window::initialized = true;
    }

    Window::~Window()
    {
        LOG("Destroying Window");
        glfwDestroyWindow(m_window);
    }

    void Window::setCurrent()
    {
        glfwMakeContextCurrent(m_window);
    }
    void Window::display()
    {
        glfwSwapBuffers(m_window);
    }

    void Window::clear()
    {
        setCurrent();
        glClearColor(1.0f, 0.7, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    int Window::getWidth()
    {
        int width, height;
        glfwGetWindowSize(m_window, &width, &height);

        return width;
    }

    int Window::getHeight()
    {
        int width, height;
        glfwGetWindowSize(m_window, &width, &height);

        return height;
    }

}  // namespace Dawn