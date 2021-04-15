#pragma once
#include "DawnPCH.h"

#include "Core/KeyCode.h"
#include "GLFW/glfw3.h"
#include "imgui_impl_opengl3.h"
#include "Core/Event.h"
#include "Core/Window.h"

//TODO: A lot of magic numbers and strings in here. Needs to be cleaned up eventually

namespace Dawn
{
    class DawnImGuiContext
    {
       private:
        void ImGuiMousePressedCallback(const Event& e)
        {
            const MousePressedEvent& m_e = (const MousePressedEvent&)e;
            int button = (int)m_e.getMouseCode();
            if (button < 3) {
                ImGuiIO& io = ImGui::GetIO();
                io.MouseDown[button] = true;
            }
        }

        void ImGuiMouseReleasedCallback(const Event& e)
        {
            const MouseReleasedEvent& m_e = (const MouseReleasedEvent&)e;
            int button = (int)m_e.getMouseCode();
            if (button < 3) {
                ImGuiIO& io = ImGui::GetIO();
                io.MouseDown[button] = false;
            }
        }

        void ImGuiMouseMovedCallback(const Event& e)
        {
            const MouseMovedEvent& m_e = (const MouseMovedEvent&)e;

            ImGuiIO& io = ImGui::GetIO();
            io.MousePos = ImVec2(m_e.getX(), m_e.getY());
        }

        void ImGuiMouseScrolledCallback(const Event& e)
        {
            const MouseScrolledEvent& m_e = (const MouseScrolledEvent&)e;

            ImGuiIO& io = ImGui::GetIO();
            io.MouseWheelH += m_e.getX();
            io.MouseWheel += m_e.getY();
        }

        void UpdateKeyModifiers()
        {
            ImGuiIO& io = ImGui::GetIO();
            io.KeyCtrl = io.KeysDown[(int)KeyCode::LeftControl] || io.KeysDown[(int)KeyCode::RightControl];
            io.KeyShift = io.KeysDown[(int)KeyCode::LeftShift] || io.KeysDown[(int)KeyCode::RightShift];
            io.KeyAlt = io.KeysDown[(int)KeyCode::LeftAlt] || io.KeysDown[(int)KeyCode::RightAlt];

#ifdef _WIN32
            io.KeySuper = false;
#else
            io.KeySuper = io.KeysDown[(int)KeyCode::LeftSuper] || io.KeysDown[(int)KeyCode::RightSuper];
#endif
        }

        void ImGuiKeyPressedCallback(const Event& e)
        {
            const KeyPressedEvent& k_e = (const KeyPressedEvent&)e;

            ImGuiIO& io = ImGui::GetIO();

            io.KeysDown[(int)k_e.getKeyCode()] = true;
            UpdateKeyModifiers();
        }

        void ImGuiKeyReleasedCallback(const Event& e)
        {
            const KeyReleasedEvent& k_e = (const KeyReleasedEvent&)e;

            ImGuiIO& io = ImGui::GetIO();

            io.KeysDown[(int)k_e.getKeyCode()] = false;
            UpdateKeyModifiers();
        }

        void ImGuiCharTypedCallback(const Event& e)
        {
            const CharTypedEvent& c_e = (const CharTypedEvent&)e;

            ImGuiIO& io = ImGui::GetIO();
            io.AddInputCharacter((unsigned int)c_e.getKeyCode());
        }

       public:
        DawnImGuiContext(std::shared_ptr<Window> window)
            : m_window(window)
        {
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();

            io.IniFilename = NULL;

            io.KeyMap[ImGuiKey_Tab] = (int)KeyCode::Tab;
            io.KeyMap[ImGuiKey_LeftArrow] = (int)KeyCode::Left;
            io.KeyMap[ImGuiKey_RightArrow] = (int)KeyCode::Right;
            io.KeyMap[ImGuiKey_UpArrow] = (int)KeyCode::Up;
            io.KeyMap[ImGuiKey_DownArrow] = (int)KeyCode::Down;
            io.KeyMap[ImGuiKey_Home] = (int)KeyCode::Home;
            io.KeyMap[ImGuiKey_End] = (int)KeyCode::End;
            io.KeyMap[ImGuiKey_Delete] = (int)KeyCode::Delete;
            io.KeyMap[ImGuiKey_Backspace] = (int)KeyCode::Backspace;
            io.KeyMap[ImGuiKey_Enter] = (int)KeyCode::Enter;
            io.KeyMap[ImGuiKey_Escape] = (int)KeyCode::Escape;
            io.KeyMap[ImGuiKey_A] = (int)KeyCode::A;
            io.KeyMap[ImGuiKey_C] = (int)KeyCode::C;
            io.KeyMap[ImGuiKey_V] = (int)KeyCode::V;
            io.KeyMap[ImGuiKey_X] = (int)KeyCode::X;
            io.KeyMap[ImGuiKey_Y] = (int)KeyCode::Y;
            io.KeyMap[ImGuiKey_Z] = (int)KeyCode::Z;

            ImGui_ImplOpenGL3_Init("#version 330 core");

            EventHandler::Listen(EventType::MousePressed, BIND_EVENT_MEMBER_FN(DawnImGuiContext::ImGuiMousePressedCallback));
            EventHandler::Listen(EventType::MouseReleased, BIND_EVENT_MEMBER_FN(DawnImGuiContext::ImGuiMouseReleasedCallback));
            EventHandler::Listen(EventType::MouseMoved, BIND_EVENT_MEMBER_FN(DawnImGuiContext::ImGuiMouseMovedCallback));
            EventHandler::Listen(EventType::MouseScrolled, BIND_EVENT_MEMBER_FN(DawnImGuiContext::ImGuiMouseScrolledCallback));
            EventHandler::Listen(EventType::KeyPressed, BIND_EVENT_MEMBER_FN(DawnImGuiContext::ImGuiKeyPressedCallback));
            EventHandler::Listen(EventType::KeyReleased, BIND_EVENT_MEMBER_FN(DawnImGuiContext::ImGuiKeyReleasedCallback));
            EventHandler::Listen(EventType::CharTyped, BIND_EVENT_MEMBER_FN(DawnImGuiContext::ImGuiCharTypedCallback));
        }

        void onUpdate()
        {
            ImGuiIO& io = ImGui::GetIO();
            io.DeltaTime = 1.0f / 60.0f;
            io.DisplaySize = ImVec2(m_window->getWidth(), m_window->getHeight());
            io.FontGlobalScale = 1.5f;

            ImGui_ImplOpenGL3_NewFrame();
            ImGui::NewFrame();
        }

        void onLateUpdate()
        {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        void onClose()
        {
            ImGui_ImplOpenGL3_Shutdown();
        }

       private:
        std::shared_ptr<Window> m_window;
    };

}  // namespace Dawn