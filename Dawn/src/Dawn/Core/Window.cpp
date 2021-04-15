#include "Window.h"

#include "Log.h"
#include "glad/glad.h"

namespace Dawn
{
    bool Window::initialized = false;

    void Window::onResize(const Event& e)
    {
        const WindowResizedEvent& w_e = (const WindowResizedEvent&)e;

        glViewport(0, 0, w_e.getWidth(), w_e.getHeight());
        m_width = w_e.getWidth();
        m_height = w_e.getHeight();
    }

    Window::Window(int width, int height, const std::string& name)
        : m_width(width), m_height(height)
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

        //TEMP
        //TODO: Add Vsync function
        //glfwSwapInterval(0);

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

        //CharTyped
        glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int codepoint) {
            EventHandler::Submit(CharTypedEvent(static_cast<KeyCode>(codepoint)));
        });

        //MouseMoved
        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x, double y) { EventHandler::Submit(MouseMovedEvent(static_cast<float>(x), static_cast<float>(y))); });

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

        EventHandler::Listen(EventType::WindowResized, BIND_EVENT_MEMBER_FN(Window::onResize));
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
        //1.0f, 0.7f, 0.1f, 1.0f
        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::setWidth(int width)
    {
        m_width = width;
        glfwSetWindowSize(m_window, m_width, m_height);
        EventHandler::Submit(WindowResizedEvent(m_width, m_height));
    }

    void Window::setHeight(int height)
    {
        m_height = height;
        glfwSetWindowSize(m_window, m_width, m_height);
        EventHandler::Submit(WindowResizedEvent(m_width, m_height));
    }

    int Window::getWidth()
    {
        return m_width;
    }

    int Window::getHeight()
    {
        return m_height;
    }

}  // namespace Dawn