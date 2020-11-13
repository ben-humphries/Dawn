#pragma once

#include "../Core/Application.h"
#include "../Core/KeyCode.h"
#include "GLFW/glfw3.h"
#include "imgui_impl_opengl3.h"

//TODO: A lot of magic numbers and strings in here. Needs to be cleaned up eventually
//TODO: Consider, instead of inheritance, make this class a private member variable of Application, and if ImGui is enabled, call these functions, otherwise, don't.
// This removes the need to call super functions (No triple inheritance).

//When inheriting this class, make sure to call the super methods of any virtual functions you override.
//i.e. if you override onUpdate, make sure to include the line
//ImGuiApplication::onUpdate();
//somewhere in your function.
namespace Dawn
{
    class ImGuiApplication : public Application
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
        ImGuiApplication()
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

            EventHandler::Listen(EventType::MousePressed, BIND_EVENT_MEMBER_FN(ImGuiMousePressedCallback));
            EventHandler::Listen(EventType::MouseReleased, BIND_EVENT_MEMBER_FN(ImGuiMouseReleasedCallback));
            EventHandler::Listen(EventType::MouseMoved, BIND_EVENT_MEMBER_FN(ImGuiMouseMovedCallback));
            EventHandler::Listen(EventType::MouseScrolled, BIND_EVENT_MEMBER_FN(ImGuiMouseScrolledCallback));
            EventHandler::Listen(EventType::KeyPressed, BIND_EVENT_MEMBER_FN(ImGuiKeyPressedCallback));
            EventHandler::Listen(EventType::KeyReleased, BIND_EVENT_MEMBER_FN(ImGuiKeyReleasedCallback));
            EventHandler::Listen(EventType::CharTyped, BIND_EVENT_MEMBER_FN(ImGuiCharTypedCallback));
        }

        void onUpdate() override
        {
            ImGuiIO& io = ImGui::GetIO();
            io.DeltaTime = 1.0f / 60.0f;
            io.DisplaySize = ImVec2(m_window->getWidth(), m_window->getHeight());

            ImGui_ImplOpenGL3_NewFrame();
            ImGui::NewFrame();

            static bool show = true;
            ImGui::ShowDemoWindow(&show);
        }

        void onLateUpdate() override
        {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        void onClose() override
        {
            ImGui_ImplOpenGL3_Shutdown();
        }
    };

}  // namespace Dawn