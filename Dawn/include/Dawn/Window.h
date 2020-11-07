#pragma once

#include <string>

#include "GLFW/glfw3.h"

namespace Dawn
{
    class Window
    {
       public:
        Window(int width = 800, int height = 600,
               const std::string& name = "Dawn App");
        ~Window();

        void onUpdate();

        void display();

        void clear();

        int getWidth();
        int getHeight();

       private:
        void setCurrent();

        GLFWwindow* m_window;

        static bool initialized;
    };
}  // namespace Dawn