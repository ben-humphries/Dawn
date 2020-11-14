#include "Application.h"

#include <iostream>

#include "Log.h"

namespace Dawn
{
    std::shared_ptr<Window> Application::m_window;
    std::unique_ptr<DawnImGuiContext> Application::m_imguiContext;

    void Application::onWindowClose(const Event& e)
    {
        m_running = false;
    }

    Application::Application()
    {
        m_window = std::make_shared<Window>();
        EventHandler::Listen(EventType::WindowClosed, BIND_EVENT_MEMBER_FN(Application::onWindowClose));

#ifdef DAWN_IMGUI
        m_imguiContext = std::make_unique<DawnImGuiContext>(m_window);
#else
        m_imguiContext = nullptr;
#endif
    }

    void Application::onEngineUpdate()
    {
        m_window->onUpdate();
        m_window->clear();
    }

    void Application::onEngineLateUpdate()
    {
        m_window->display();
    }

    void Application::onEngineClose()
    {
    }

    void Application::start()
    {
        // Main Loop
        while (m_running) {
            onEngineUpdate();
            if (m_imguiContext) m_imguiContext->onUpdate();
            onUpdate();
            if (m_imguiContext) onImGuiUpdate();
            onLateUpdate();
            if (m_imguiContext) m_imguiContext->onLateUpdate();
            onEngineLateUpdate();
        }

        close();
    }

    void Application::close()
    {
        if (m_imguiContext) m_imguiContext->onClose();
        glfwTerminate();
    }
}  // namespace Dawn