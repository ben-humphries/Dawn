#pragma once

namespace Dawn
{
    class Time
    {
       public:
        static float deltaTime;
        static float fixedDeltaTime;

       private:
        static void UpdateTimestep();
        static float lastFrameTime;

        friend class Application;
    };
}