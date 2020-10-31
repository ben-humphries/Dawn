#pragma once

#include "GLFW/glfw3.h"

namespace Dawn
{
    class Window
    {
       public:
        Window(int width, int height, const char* name);
        ~Window();

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