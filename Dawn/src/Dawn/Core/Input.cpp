#include "Input.h"

#include "Application.h"

namespace Dawn
{
    bool Input::GetKeyDown(KeyCode key)
    {
        GLFWwindow *window = static_cast<GLFWwindow *>(Application::window->getNativeWindow());

        return glfwGetKey(window, static_cast<int>(key)) == GLFW_PRESS;
    }

    bool Input::GetMouseButtonDown(MouseCode button)
    {
        GLFWwindow *window = static_cast<GLFWwindow *>(Application::window->getNativeWindow());

        return glfwGetMouseButton(window, static_cast<int>(button)) == GLFW_PRESS;
    }
}