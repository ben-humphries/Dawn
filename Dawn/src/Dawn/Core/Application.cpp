#include "Application.h"

#include <iostream>

#include "Log.h"

namespace Dawn
{
    std::unique_ptr<Window> Application::window;

    void Application::onWindowClose(const Event& e)
    {
        running = false;
    }

    Application::Application()
    {
        window = std::make_unique<Window>();
        EventHandler::Listen(WindowClosed, BIND_EVENT_MEMBER_FN(Application::onWindowClose));
    }

    void Application::onEngineUpdate()
    {
        window->onUpdate();
        window->clear();
    }

    void Application::onEngineLateUpdate()
    {
        window->display();
    }

    void Application::onEngineClose()
    {
    }

    void Application::start()
    {
        // Main Event Loop
        while (running) {
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