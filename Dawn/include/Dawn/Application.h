#pragma once

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace Dawn
{
    class Application
    {
       public:
        // Derived class must implement these functions
        virtual void Init() = 0;
        virtual void Update() = 0;

        // Calls init methods, and then enters game loop
        void Start();
        void Close();

       private:
        void EngineInit();
        void EngineUpdate();

        GLFWwindow* m_window;
    };
}  // namespace Dawn
