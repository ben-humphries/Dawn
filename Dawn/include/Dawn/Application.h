#pragma once

#include "Dawn/Window.h"

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
    };
}  // namespace Dawn
