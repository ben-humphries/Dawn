#pragma once

#include <memory>

#include "Event.h"
#include "Window.h"

namespace Dawn
{
    class Application
    {
       public:
        Application();

        // Derived class must implement pure virtual functions
        virtual void onUpdate() = 0;
        virtual void onLateUpdate(){};
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
        static std::unique_ptr<Window> m_window;
        bool m_running = true;

        friend class Input;
        friend class ImGuiApplication;
    };
}  // namespace Dawn
