#pragma once
#include "DawnPCH.h"

#include "Event.h"
#include "Window.h"

#include "../ImGui/DawnImGuiContext.h"

#define DAWN_IMGUI

namespace Dawn
{
    class Application
    {
       public:
        Application();

        // Derived class must implement pure virtual functions
        virtual void onUpdate() = 0;
        virtual void onLateUpdate(){};
        virtual void onImGuiUpdate(){};
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
        static std::shared_ptr<Window> m_window;
        static std::unique_ptr<DawnImGuiContext> m_imguiContext;
        bool m_running = true;

        friend class Input;
    };
}  // namespace Dawn
