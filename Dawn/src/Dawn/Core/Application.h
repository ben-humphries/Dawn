#pragma once

#include <memory>

#include "Window.h"
#include "Event.h"

namespace Dawn
{
    class Application
    {
       public:
        Application();

        // Derived class must implement these functions
        virtual void onUpdate() = 0;
        virtual void onClose() = 0;

        // Enters game loop
        void start();
        // Called after game loop finishes
        void close();

       private:
        void onEngineUpdate();
        void onEngineLateUpdate();
        void onEngineClose();

        void onWindowClose(const Event& e);

       private:
        //This is static so that the Input class can access it. Possibly change in the future?
        static std::unique_ptr<Window> window;
        bool running = true;

        friend class Input;
    };
}  // namespace Dawn
