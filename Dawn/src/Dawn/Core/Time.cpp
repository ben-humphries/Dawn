#include "Time.h"

#include "glfw/glfw3.h"

namespace Dawn
{
    float Time::deltaTime = 0.0f;
    float Time::fixedDeltaTime = 1.0 / 60.0f;

    float Time::lastFrameTime = 0.0f;

    void Time::UpdateTimestep()
    {
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrameTime;

        lastFrameTime = currentTime;
    }
}