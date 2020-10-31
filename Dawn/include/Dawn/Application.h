#pragma once

#include <memory>

#include "Dawn/Window.h"

namespace Dawn
{
    class Application
    {
       public:
        Application();

        // Derived class must implement these functions
        virtual void OnUpdate() = 0;
        virtual void OnClose() = 0;

        // Enters game loop
        void Start();
        // Called after game loop finishes
        void Close();

       private:
        void OnEngineUpdate();
        void OnEngineClose();

       private:
        std::unique_ptr<Window> window;
    };
}  // namespace Dawn
