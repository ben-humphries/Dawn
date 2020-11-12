#include "Application.h"

#include <iostream>

#include "Log.h"

namespace Dawn
{
    std::unique_ptr<Window> Application::m_window;

    void Application::onWindowClose(const Event& e)
    {
        m_running = false;
    }

    Application::Application()
    {
        m_window = std::make_unique<Window>();
        EventHandler::Listen(EventType::WindowClosed, BIND_EVENT_MEMBER_FN(Application::onWindowClose));
    }

    void Application::onEngineUpdate()
    {
        m_window->onUpdate();
        m_window->clear();
    }

    void Application::onEngineLateUpdate()
    {
        m_window->display();
    }

    void Application::onEngineClose()
    {
    }

    void Application::start()
    {
        // Main Event Loop
        while (m_running) {
            onEngineUpdate();
            onUpdate();
            onEngineLateUpdate();
        }

        close();
    }

    void Application::close()
    {
        glfwTerminate();
    }
}  // namespace Dawn