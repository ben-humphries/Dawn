#pragma once

#include <string>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "Event.h"

namespace Dawn
{
    class Window
    {
       public:
        Window(int width = 1920, int height = 1920,
               const std::string& name = "Dawn App");
        ~Window();

        void* getNativeWindow()
        {
            return (void*)m_window;
        }

        void onUpdate();

        void display();

        void clear();

        int getWidth();
        int getHeight();

       private:
        void setCurrent();
        void onResize(const Event& e);

        GLFWwindow* m_window;

        static bool initialized;
    };
}  // namespace Dawn