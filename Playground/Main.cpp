#include "Dawn/Dawn.h"
#include "imgui_internal.h"

//TEMP
#include "glad/glad.h"

#define IMGUI_DEFINE_MATH_OPERATORS

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

    Dawn::Scene scene = Dawn::Scene();

    //IMGUI
    float leftPanelSizeLeft = 400;
    float leftPanelSizeRight = 1920 - 440;

    ImVec2 viewportPanelSize = ImVec2(0, 0);

    Playground()
    {
        tex1.loadFromFile("test.png");
        tex2.loadFromFile("test2.png");

        auto& scene_registry = scene.getRegistry();

        for (int i = 0; i < 10; i++) {
            Dawn::Entity e = scene_registry.addEntity();

            scene_registry.addComponent<Dawn::TransformComponent>(e);
            auto& transform = scene_registry.getComponent<Dawn::TransformComponent>(e);
            transform.position = Dawn::Vec3(i, 0, 0);
            transform.scale = Dawn::Vec3(0.5);

            scene_registry.addComponent<Dawn::SpriteRendererComponent>(e);
            auto& spriteRenderer = scene_registry.getComponent<Dawn::SpriteRendererComponent>(e);
            spriteRenderer.color = Dawn::Vec4(0.5, 0.6, 0.2, 1);
        }

        //ENTITY TEST
        // Dawn::EntityRegistry registry;
        // Dawn::Entity e = registry.addEntity();
        // Dawn::Entity e2 = registry.addEntity();
        // Dawn::Entity e3 = registry.addEntity();
        // registry.addComponent<Dawn::TransformComponent>(e);
        // registry.addComponent<Dawn::RenderComponent>(e);

        // registry.addComponent<Dawn::TransformComponent>(e2);

        // registry.addComponent<Dawn::RenderComponent>(e3);

        // Dawn::TransformComponent transform = registry.getComponent<Dawn::TransformComponent>(e);
        // auto render = registry.getComponent<Dawn::RenderComponent>(e);

        // registry.deleteEntity(e2);
        // //registry.deleteComponent<Dawn::TransformComponent>(e);

        // Dawn::Entity e4 = registry.addEntity();
        // registry.addComponent<Dawn::TransformComponent>(e4);
        // registry.addComponent<Dawn::RenderComponent>(e4);

        // auto list1 = registry.getEntitiesWithComponents<Dawn::TransformComponent, Dawn::RenderComponent>();

        // auto list2 = registry.getComponentsOfType<Dawn::TransformComponent>();
        // DAWN_LOG(list2[0]->pos);

        // transform.pos = 10;
        // transform.scale = 4;
        // DAWN_LOG(render.test);
        // DAWN_LOG(transform.s_id);
        ///
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
            //scene.getMainCamera()->setProjection(-aspectRatio * zoom, aspectRatio * zoom, -1.0 * zoom, 1.0 * zoom);
            camera.setProjection(-aspectRatio * zoom, aspectRatio * zoom, -1.0 * zoom, 1.0 * zoom);
        }

        fb.bind();
        glClearColor(0.2, 0.2, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        camera.setPosition(Dawn::Vec3(0, 0, -1));
        //camera.setRotation(-quadRotation);

        // Dawn::Renderer2D::StartFrame(camera);
        // //clear color

        // Dawn::Renderer2D::DrawQuad(Dawn::Vec3(0, 0, 0), quadRotation, Dawn::Vec3(1.0), quadColor, &tex2);
        // Dawn::Renderer2D::DrawQuad(Dawn::Vec3(-0.5, 0, 0), 0, Dawn::Vec3(0.5), Dawn::Vec4(1.0, 1.0, 1.0, 1.0), &tex1);
        // Dawn::Renderer2D::DrawQuad(Dawn::Vec3(-0.5, -0.5, 0), 0, Dawn::Vec3(0.5), quadColor);

        //scene.onUpdate();
        scene.getRegistry().getComponentsOfType<Dawn::TransformComponent>();

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

        //Dawn::Renderer2D::EndFrame();
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