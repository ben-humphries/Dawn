#include "Window.h"

#include "glad/glad.h"

#include "Log.h"
#include "Event.h"

namespace Dawn
{
    bool Window::initialized = false;

    Window::Window(int width, int height, const std::string& name)
    {
        if (!Window::initialized) {
            if (glfwInit() == GLFW_FALSE) {
                LOG("Failed to initialize GLFW");
            }
        }
        // Create GLFW Window
        m_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
        if (m_window == NULL) {
            LOG("Failed to create GLFW window");
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(m_window);

        if (!Window::initialized) {
            //Initialize Glad
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                LOG("Failed to initialize Glad");
                return;
            }
        }

        glViewport(0, 0, width, height);

        Window::initialized = true;

        //Set GLFW callbacks

        //WindowClosed
        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* w) {
            EventHandler::Submit(WindowClosedEvent());
        });

        //WindowResized
        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* w, int width, int height) {
            EventHandler::Submit(WindowResizedEvent(width, height));
        });

        //WindowMoved
        glfwSetWindowPosCallback(m_window, [](GLFWwindow* window, int x, int y) {
            EventHandler::Submit(WindowMovedEvent(x, y));
        });

        //KeyPressed and KeyReleased
        glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            if (action == GLFW_PRESS)
                EventHandler::Submit(KeyPressedEvent(static_cast<KeyCode>(key)));
            else if (action == GLFW_RELEASE)
                EventHandler::Submit(KeyReleasedEvent(static_cast<KeyCode>(key)));
        });

        //MouseMoved
        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x, double y) {
            EventHandler::Submit(MouseMovedEvent(static_cast<float>(x), static_cast<float>(y)));
        });

        //MousePressed and MouseReleased
        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
            if (action == GLFW_PRESS)
                EventHandler::Submit(MousePressedEvent(static_cast<MouseCode>(button)));
            else if (action == GLFW_RELEASE)
                EventHandler::Submit(MouseReleasedEvent(static_cast<MouseCode>(button)));
        });

        //MouseScrolled
        glfwSetScrollCallback(m_window, [](GLFWwindow* window, double x, double y) {
            EventHandler::Submit(MouseScrolledEvent(static_cast<float>(x), static_cast<float>(y)));
        });
    }

    Window::~Window()
    {
        LOG("Destroying Window");
        glfwDestroyWindow(m_window);
    }

    void Window::onUpdate()
    {
        setCurrent();
        glfwPollEvents();
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