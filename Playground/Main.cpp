#include "Dawn/Dawn.h"

//TEMP
#include "glad/glad.h"

void test(const Dawn::Event& e)
{
    DAWN_LOG(e.toString());
}

void test_keycodes(const Dawn::Event& e)
{
    auto e_k = (const Dawn::KeyPressedEvent&)e;
    if (e_k.getKeyCode() == Dawn::KeyCode::A) {
        DAWN_LOG("Key A was pressed");
    }
}

class Playground : public Dawn::Application
{
   public:
    Dawn::Vec4 quadColor = Dawn::Vec4(1, 0, 1, 1);
    float quadRotation = 0;

    Playground()
    {
        //Register Event Callbacks
        Dawn::EventHandler::Listen(Dawn::EventType::WindowClosed, test);
        Dawn::EventHandler::Listen(Dawn::EventType::WindowResized, test);
        Dawn::EventHandler::Listen(Dawn::EventType::WindowMoved, test);
        Dawn::EventHandler::Listen(Dawn::EventType::KeyPressed, test);
        Dawn::EventHandler::Listen(Dawn::EventType::KeyReleased, test);
        Dawn::EventHandler::Listen(Dawn::EventType::MouseMoved, test);
        Dawn::EventHandler::Listen(Dawn::EventType::MousePressed, test);
        Dawn::EventHandler::Listen(Dawn::EventType::MouseReleased, test);
        Dawn::EventHandler::Listen(Dawn::EventType::MouseScrolled, test);

        Dawn::EventHandler::Listen(Dawn::EventType::KeyPressed, test_keycodes);
    }

    void onImGuiUpdate() override
    {
        //static bool show = true;
        //ImGui::ShowDemoWindow(&show);

        ImGui::Begin("Demo window");
        ImGui::ColorPicker4("triangle color", (float*)&quadColor);
        ImGui::DragFloat("rotation", &quadRotation, 0.1f, 0.f, 6.28f, NULL, 1.f);
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "testing!");
        ImGui::TextWrapped("testetestsetset testest testing a gain this is more wrapped text let's see how this goes.");
        ImGui::SetWindowSize(ImVec2(400, 900), ImGuiCond_FirstUseEver);
        ImGui::Button("Hello!");
        ImGui::End();
    }

    void onUpdate() override
    {
        if (Dawn::Input::GetKeyDown(Dawn::KeyCode::B)) {
            DAWN_LOG("B is being pressed");
        }
        if (Dawn::Input::GetMouseButtonDown(Dawn::MouseCode::Middle)) {
            DAWN_LOG("Middle MB being pressed");
        }

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        Dawn::Renderer2D::StartFrame();
        Dawn::Renderer2D::DrawQuad(Dawn::Vec3(0.5, 0, 0), quadRotation, Dawn::Vec3(0.5), quadColor);
        // Dawn::Renderer2D::DrawQuad(Dawn::Vec3(-0.5), triangleColor);
        Dawn::Renderer2D::EndFrame();
    }

    void onClose() override
    {
    }
};

int main()
{
    Playground playground = Playground();
    playground.start();

    //Dawn::ImGuiApplication app = Dawn::ImGuiApplication();
    //app.start();

    return 0;
}