#include "Dawn/Application.h"

#include <iostream>

#include "Dawn/Log.h"

namespace Dawn
{
    void Application::EngineInit()
    {
        LOG("Logging from Dawn Engine init function");

        glfwInit();

        // Create GLFW Window
        m_window = glfwCreateWindow(800, 600, "Dawn Engine App", NULL, NULL);
        if (m_window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(m_window);

        // Initialize GLEW
        GLenum err = glewInit();
        if (GLEW_OK != err) {
            std::cout << "Failed to initialize GLEW" << std::endl;
            return;
        }
        int test = 5;
        glViewport(0, 0, 800, 600);
    }

    void Application::EngineUpdate()
    {
        LOG("Logging from Dawn Engine update function");
        glClearColor(1.0f, 0.7, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    void Application::Start()
    {
        EngineInit();
        Init();
        // Main Event Loop
        while (!glfwWindowShouldClose(m_window)) {
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