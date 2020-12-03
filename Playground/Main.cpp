#include "Dawn/Dawn.h"
#include "imgui_internal.h"

//TEMP
#include "glad/glad.h"

#define IMGUI_DEFINE_MATH_OPERATORS

void test(const Dawn::Event& e)
{
    //DAWN_LOG(e.toString());
}

void test_keycodes(const Dawn::Event& e)
{
    auto e_k = (const Dawn::KeyPressedEvent&)e;
    if (e_k.getKeyCode() == Dawn::KeyCode::A) {
        DAWN_LOG("Key A was pressed");
    }
}

void DrawSplitter(int split_vertically, float thickness, float* size0, float* size1, float min_size0, float min_size1)
{
    ImVec2 backup_pos = ImGui::GetCursorPos();
    if (split_vertically)
        ImGui::SetCursorPosY(backup_pos.y + *size0);
    else
        ImGui::SetCursorPosX(backup_pos.x + *size0);

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));  // We don't draw while active/pressed because as we move the panes the splitter button will be 1 frame late
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.6f, 0.6f, 0.6f, 0.10f));
    ImGui::Button("##Splitter", ImVec2(!split_vertically ? thickness : -1.0f, split_vertically ? thickness : -1.0f));
    ImGui::PopStyleColor(3);

    ImGui::SetItemAllowOverlap();  // This is to allow having other buttons OVER our splitter.

    if (ImGui::IsItemActive()) {
        float mouse_delta = split_vertically ? ImGui::GetIO().MouseDelta.y : ImGui::GetIO().MouseDelta.x;

        //Minimum pane size
        if (mouse_delta < min_size0 - *size0)
            mouse_delta = min_size0 - *size0;
        if (mouse_delta > *size1 - min_size1)
            mouse_delta = *size1 - min_size1;

        // Apply resize
        *size0 += mouse_delta;
        *size1 -= mouse_delta;
    }
    ImGui::SetCursorPos(backup_pos);
}

//////////////////////PLAYGROUND CLASS///////////////////////////
class Playground : public Dawn::Application
{
   public:
    Dawn::OrthographicCamera camera = Dawn::OrthographicCamera(-1.0, 1.0, -0.5, 0.5);
    float zoom = 1.0f;

    Dawn::Vec4 quadColor = Dawn::Vec4(1, 0, 1, 1);
    float quadRotation = 0;
    float quadPosition = 0;

    Dawn::Texture tex1;
    Dawn::Texture tex2;

    //get window width and height
    Dawn::Framebuffer fb = Dawn::Framebuffer(1920, 1920);

    //IMGUI
    float leftPanelSizeLeft = 400;
    float leftPanelSizeRight = 1920 - 440;

    ImVec2 viewportPanelSize = ImVec2(0, 0);

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

        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

        //TODO: Resizing doesn't completely work and can glitch out after resizing the window
        //TODO: Resize frame buffer
        ImGui::SetNextWindowSize(ImVec2(getWindow().getWidth(), getWindow().getHeight()));
        ImGui::Begin("Main Window", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
        ImGui::SetWindowPos(ImVec2(0, 0));

        //MENU BAR
        ImVec2 menuBarSize;
        if (ImGui::BeginMenuBar()) {
            menuBarSize = ImGui::GetWindowSize();
            if (ImGui::BeginMenu("File")) {
                if (ImGui::BeginMenu("Open")) {
                    if (ImGui::MenuItem("test")) {
                        DAWN_LOG("Opened something");
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        //LEFT PANEL
        DrawSplitter(false, 10, &leftPanelSizeLeft, &leftPanelSizeRight, 400, 0);
        ImGui::BeginChild("Left Panel", ImVec2(leftPanelSizeLeft, getWindow().getHeight() - menuBarSize.y), true);
        ImGui::ColorPicker4("quad color", (float*)&quadColor);
        ImGui::DragFloat("rotation", &quadRotation, 0.1f, 0.f, 6.28f, NULL, 1.f);
        ImGui::DragFloat("position", &quadPosition, 0.1f, -1.f, 1.0f, NULL, 1.f);
        ImGui::DragFloat("camera zoom", &zoom, 0.1f, 0.0f, 10.0f, NULL, 1.f);

        std::string fps = "FPS: " + std::to_string(1.0f / Dawn::Time::deltaTime);
        ImGui::TextColored(ImVec4(1, 0, 0, 1), fps.c_str());

        std::string memory = "Heap Memory Allocated: " + std::to_string(Dawn::Memory::GetCurrentlyAllocated()) + " bytes";
        ImGui::Text(memory.c_str());
        std::string allocations = "Total Allocations: " + std::to_string(Dawn::Memory::GetAllocations());
        ImGui::Text(allocations.c_str());

        for (auto scopeTime : Dawn::ProfileTimer::s_scopeTimes) {
            std::string display = std::to_string(scopeTime.time) + "s || " + scopeTime.name;
            ImGui::Text(display.c_str());
        }
        Dawn::ProfileTimer::s_scopeTimes.clear();
        ImGui::EndChild();

        ImGui::SameLine();
        ImGui::BeginChild("Right Panel", ImVec2(getWindow().getWidth() - leftPanelSizeLeft - 20 - 5, getWindow().getHeight() - menuBarSize.y), true);

        viewportPanelSize = ImGui::GetContentRegionAvail();
        ImGui::Image((void*)fb.getColorTextureHandle(), viewportPanelSize, ImVec2(0, 1), ImVec2(1, 0));

        ImGui::EndChild();

        ImGui::End();  //Main Window

        ImGui::PopStyleVar(2);

        //DEMO WINDOW
        //static bool show = true;
        //ImGui::ShowDemoWindow(&show);
    }

    void onUpdate() override
    {
        DAWN_PROFILE_FUNC();

        if (Dawn::Input::GetKeyDown(Dawn::KeyCode::B)) {
            DAWN_LOG("B is being pressed");
        }
        if (Dawn::Input::GetMouseButtonDown(Dawn::MouseCode::Middle)) {
            DAWN_LOG("Middle MB being pressed");
        }

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        if (viewportPanelSize.x > 0 && viewportPanelSize.y > 0) {
            fb.resize(viewportPanelSize.x, viewportPanelSize.y);
            float normalizedX = viewportPanelSize.x / sqrt(viewportPanelSize.x * viewportPanelSize.x + viewportPanelSize.y * viewportPanelSize.y);
            float normalizedY = viewportPanelSize.y / sqrt(viewportPanelSize.x * viewportPanelSize.x + viewportPanelSize.y * viewportPanelSize.y);

            float aspectRatio = viewportPanelSize.x / viewportPanelSize.y;
            camera.setProjection(-aspectRatio * zoom, aspectRatio * zoom, -1.0 * zoom, 1.0 * zoom);
        }

        fb.bind();
        glClearColor(0.2, 0.2, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        camera.setPosition(Dawn::Vec3(0, 0, -1));
        //camera.setRotation(-quadRotation);

        Dawn::Renderer2D::StartFrame(camera);
        //clear color

        Dawn::Renderer2D::DrawQuad(Dawn::Vec3(0, 0, 0), quadRotation, Dawn::Vec3(1.0), quadColor, &tex2);
        Dawn::Renderer2D::DrawQuad(Dawn::Vec3(-0.5, 0, 0), 0, Dawn::Vec3(0.5), Dawn::Vec4(1.0, 1.0, 1.0, 1.0), &tex1);
        Dawn::Renderer2D::DrawQuad(Dawn::Vec3(-0.5, -0.5, 0), 0, Dawn::Vec3(0.5), quadColor);

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

        Dawn::Renderer2D::EndFrame();
        fb.unbind();

        //ImGui::Image((ImTextureID)fb.getColorTextureHandle(), ImVec2(1920, 1920));
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