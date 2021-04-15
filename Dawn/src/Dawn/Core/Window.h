#pragma once
#include "DawnPCH.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "Event.h"

namespace Dawn
{
    class Window
    {
       public:
        Window(int width = 800, int height = 600,
               const std::string& name = "Dawn App");
        ~Window();

        void* getNativeWindow()
        {
            return (void*)m_window;
        }

        void onUpdate();

        void display();

        void clear();

        void setWidth(int width);
        void setHeight(int height);

        int getWidth();
        int getHeight();

       private:
        void setCurrent();
        void onResize(const Event& e);

        GLFWwindow* m_window;

        int m_width, m_height;

        static bool initialized;
    };
}  // namespace Dawn