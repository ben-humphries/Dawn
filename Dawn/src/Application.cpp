#include "Dawn/Application.h"

#include <iostream>

#include "Dawn/Log.h"

namespace Dawn
{
    Application::Application()
    {
        window = std::make_unique<Window>();
    }

    void Application::OnEngineUpdate()
    {
        window->clear();
        window->display();
    }

    void Application::OnEngineClose()
    {
    }

    void Application::Start()
    {
        // Main Event Loop
        while (true) {
            OnEngineUpdate();
            OnUpdate();
        }

        Close();
    }

    void Application::Close()
    {
        glfwTerminate();
    }
}  // namespace Dawn