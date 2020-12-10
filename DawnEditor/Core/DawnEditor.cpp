#include "DawnEditor.h"

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

namespace Dawn
{
    DawnEditor::DawnEditor()
        : m_sceneHierarchyPanel(&scene)
    {
        tex1.loadFromFile("test.png");
        tex2.loadFromFile("test2.png");

        parentsParent = scene.addEntity();
        scene.addComponent<Dawn::TransformComponent>(parentsParent);
        scene.addComponent<Dawn::SpriteRendererComponent>(parentsParent);
        auto& parentsParentSprite = scene.getComponent<Dawn::SpriteRendererComponent>(parentsParent);
        parentsParentSprite.texture = &tex2;
        auto& ppTag = scene.getComponent<Dawn::TagComponent>(parentsParent);
        ppTag.tag = "parent's parent";

        parent = scene.addEntity();
        scene.addComponent<Dawn::TransformComponent>(parent);
        scene.addComponent<Dawn::ParentComponent>(parent);
        scene.addComponent<Dawn::SpriteRendererComponent>(parent);
        auto& parentSprite = scene.getComponent<Dawn::SpriteRendererComponent>(parent);
        parentSprite.texture = &tex1;
        auto& pTag = scene.getComponent<Dawn::TagComponent>(parent);
        pTag.tag = "parent";

        scene.makeEntityChild(parent, parentsParent);

        for (int i = 0; i < 10; i++) {
            Dawn::Entity e = scene.addEntity();

            scene.addComponent<Dawn::TransformComponent>(e);
            auto& transform = scene.getComponent<Dawn::TransformComponent>(e);
            transform.position = Dawn::Vec3(i, 0, 0);
            transform.scale = Dawn::Vec3(0.5);
            transform.rotation = i;

            scene.addComponent<Dawn::SpriteRendererComponent>(e);
            auto& spriteRenderer = scene.getComponent<Dawn::SpriteRendererComponent>(e);
            spriteRenderer.color = Dawn::Vec4(0.5, 0.6, 0.2, 1);

            auto& tag = scene.getComponent<Dawn::TagComponent>(e);
            tag.tag = "green square" + std::to_string(i);

            scene.makeEntityChild(e, parent);
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

        //         Dawn::Entity e = scene.addEntity();

        //         scene.addComponent<Dawn::TransformComponent>(e);
        //         auto& transform = scene.getComponent<Dawn::TransformComponent>(e);
        //         transform.position = Dawn::Vec3(x, y, 0);
        //         transform.scale = Dawn::Vec3(.02, .02, 1.0);

        //         scene.addComponent<Dawn::SpriteRendererComponent>(e);
        //         auto& spriteRenderer = scene.getComponent<Dawn::SpriteRendererComponent>(e);
        //         spriteRenderer.texture = tex;
        //         spriteRenderer.color = Dawn::Vec4((x + 1) / 2, (y + 1) / 2, 1.0, 1.0);
        //     }
        // }

        // DAWN_LOG(quads);
    }

    void DawnEditor::onUpdate()
    {
        if (Dawn::Input::GetKeyDown(Dawn::KeyCode::B)) {
            DAWN_LOG("B is being pressed");
        }
        if (Dawn::Input::GetMouseButtonDown(Dawn::MouseCode::Middle)) {
            DAWN_LOG("Middle MB being pressed");
        }

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        if (viewportPanelSize.x > 0 && viewportPanelSize.y > 0) {
            fb.resize(viewportPanelSize.x, viewportPanelSize.y);

            float aspectRatio = viewportPanelSize.x / viewportPanelSize.y;
            scene.getMainCamera()->setProjection(-aspectRatio * zoom, aspectRatio * zoom, -1.0 * zoom, 1.0 * zoom);
        }

        fb.bind();
        this->clearWindow();
        scene.onUpdate();

        fb.unbind();
    }

    void DawnEditor::onImGuiUpdate()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

        ImGui::SetNextWindowSize(ImVec2(400, getWindow().getHeight()));
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        m_sceneHierarchyPanel.drawPanel();

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
        ImGui::DragFloat("camera zoom", &zoom, 0.1f, 0.0f, 10.0f, NULL, 1.f);

        auto& ptransform = scene.getComponent<Dawn::TransformComponent>(parentsParent);
        ImGui::DragFloat3("parentsParent position", (float*)&ptransform.position, 0.1f, -10.0f, 10.0f, NULL, 1.f);
        ImGui::DragFloat("parentsParent rotation", &ptransform.rotation, 0.1f, 0.f, 6.28f, NULL, 1.f);
        ImGui::DragFloat3("parentsParent scale", (float*)&ptransform.scale, 0.1f, -10.0f, 10.0f, NULL, 1.f);

        auto& transform = scene.getComponent<Dawn::TransformComponent>(parent);
        ImGui::DragFloat3("parent position", (float*)&transform.position, 0.1f, -10.0f, 10.0f, NULL, 1.f);
        ImGui::DragFloat("parent rotation", &transform.rotation, 0.1f, 0.f, 6.28f, NULL, 1.f);
        ImGui::DragFloat3("parent scale", (float*)&transform.scale, 0.1f, -10.0f, 10.0f, NULL, 1.f);

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
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }

    void DawnEditor::onClose()
    {
    }

}  // namespace Dawn