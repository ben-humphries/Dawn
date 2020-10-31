#include "Dawn/Application.h"

#include <iostream>

#include "Dawn/Log.h"

namespace Dawn
{
    void Application::EngineInit()
    {
    }

    void Application::EngineUpdate()
    {
    }

    void Application::Start()
    {
        EngineInit();
        Init();
        // Main Event Loop
        while (true) {
            EngineUpdate();
            Update();
        }

        Close();
    }

    void Application::Close()
    {
        glfwTerminate();
    }
}  // namespace Dawn