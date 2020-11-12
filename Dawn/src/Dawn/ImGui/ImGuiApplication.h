#pragma once

#include "../Core/Application.h"
#include "../Core/KeyCode.h"
#include "GLFW/glfw3.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//TODO: A lot of magic numbers and strings in here. Needs to be cleaned up eventually

namespace Dawn
{
    class ImGuiApplication : public Application
    {
       public:
        ImGuiApplication()
        {
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();

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

            ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window->getNativeWindow(), true);
            ImGui_ImplOpenGL3_Init("#version 330 core");
        }

        void onUpdate() override
        {
            ImGuiIO& io = ImGui::GetIO();
            io.DeltaTime = 1.0f / 60.0f;
            io.DisplaySize = ImVec2(window->getWidth(), window->getHeight());

            ImGui_ImplOpenGL3_NewFrame();
            ImGui::NewFrame();

            static bool show = true;
            ImGui::ShowDemoWindow(&show);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        void onClose() override
        {
        }
    };

}  // namespace Dawn