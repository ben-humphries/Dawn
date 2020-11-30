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

    Dawn::Texture tex1;
    Dawn::Texture tex2;

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

        tex1.loadFromFile("test.png");
        tex2.loadFromFile("test2.png");
    }

    void onImGuiUpdate() override
    {
        DAWN_PROFILE_FUNC();

        //static bool show = true;
        //ImGui::ShowDemoWindow(&show);

        ImGui::Begin("Demo window");
        ImGui::SetWindowSize(ImVec2(400, 900), ImGuiCond_FirstUseEver);

        ImGui::ColorPicker4("triangle color", (float*)&quadColor);
        ImGui::DragFloat("rotation", &quadRotation, 0.1f, 0.f, 6.28f, NULL, 1.f);
        std::string fps = "FPS: " + std::to_string(1.0f / Dawn::Time::deltaTime);
        ImGui::TextColored(ImVec4(1, 0, 0, 1), fps.c_str());

        for (auto scopeTime : Dawn::ProfileTimer::s_scopeTimes) {
            std::string display = std::to_string(scopeTime.time) + "s || " + scopeTime.name;
            ImGui::Text(display.c_str());
        }
        Dawn::ProfileTimer::s_scopeTimes.clear();

        ImGui::End();
    }

    void onUpdate() override
    {
        DAWN_PROFILE_FUNC();

        {
            DAWN_PROFILE_SCOPE("check input");
            if (Dawn::Input::GetKeyDown(Dawn::KeyCode::B)) {
                DAWN_LOG("B is being pressed");
            }
            if (Dawn::Input::GetMouseButtonDown(Dawn::MouseCode::Middle)) {
                DAWN_LOG("Middle MB being pressed");
            }
        }

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        {
            DAWN_PROFILE_SCOPE("render quads");
            Dawn::Renderer2D::StartFrame();

            Dawn::Renderer2D::DrawQuad(Dawn::Vec3(-0.5, 0, 0), 0, Dawn::Vec3(0.5), Dawn::Vec4(1.0, 1.0, 1.0, 1.0), &tex1);
            Dawn::Renderer2D::DrawQuad(Dawn::Vec3(0.5, 0, 0), quadRotation, Dawn::Vec3(0.5), quadColor, &tex2);
            Dawn::Renderer2D::DrawQuad(Dawn::Vec3(-0.5, -0.5, 0), 0, Dawn::Vec3(0.5), quadColor);
        }
        // int quads = 0;
        // for (float x = -1.0; x < 1.0; x += 0.02) {
        //     for (float y = -1.0; y < 1.0; y += 0.02) {
        //         quads++;
        //         Dawn::Texture* tex = nullptr;
        //         if (quads % 2 == 0)
        //             tex = &tex1;
        //         else {
        //             tex = &tex2;
        //         }

        //         Dawn::Renderer2D::DrawQuad(Dawn::Vec3(x, y, 0), quadRotation, Dawn::Vec3(0.02, 0.02, 1), quadColor * Dawn::Vec4((x + 1) / 2, (y + 1) / 2, 1.0, 1.0), tex);
        //     }
        // }

        //DAWN_LOG(quads);

        {
            DAWN_PROFILE_SCOPE("end frame");

            Dawn::Renderer2D::EndFrame();
        }
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