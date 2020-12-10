#include "DawnEditor.h"

namespace Dawn
{
    DawnEditor::DawnEditor()
        : m_sceneHierarchyPanel(&scene),
          m_inspectorPanel(&scene)
    {
        //IMGUI STYLE
        ImGuiStyle& style = ImGui::GetStyle();
        style.Colors[ImGuiCol_WindowBg] = ImVec4(.15f, .15f, .15f, 1.0f);
        style.Colors[ImGuiCol_TitleBg] = ImVec4(.051f, .051f, .051f, 1.0f);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(.051f, .051f, .051f, 1.0f);
        style.Colors[ImGuiCol_Header] = ImVec4(.49f, .558f, .638f, .310f);
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(.618f, .618f, .618f, .8f);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(.389f, .389f, .389f, 1.0f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(.49f, .558f, .638f, .310f);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(.49f, .558f, .638f, .310f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(.49f, .558f, .638f, .310f);

        ////

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
        m_sceneHierarchyPanel.draw();

        ImGui::SetNextWindowSize(ImVec2(400, getWindow().getHeight()));
        ImGui::SetNextWindowPos(ImVec2(getWindow().getWidth() - 400, 0));
        m_inspectorPanel.draw(m_sceneHierarchyPanel.getSelectedEntity());

        //TODO: Resizing doesn't completely work and can glitch out after resizing the window
        //TODO: Resize frame buffer
        ImGui::SetNextWindowSize(ImVec2(getWindow().getWidth() - 400 - 400, getWindow().getHeight()));
        ImGui::Begin("Viewport", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
        ImGui::SetWindowPos(ImVec2(400, 0));

        viewportPanelSize = ImGui::GetContentRegionAvail();
        ImGui::Image((void*)fb.getColorTextureHandle(), viewportPanelSize, ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();  //Main Window

        ImGui::PopStyleVar(2);

        ImGui::SetNextWindowSize(ImVec2(400, 75));
        ImGui::SetNextWindowPos(ImVec2(getWindow().getWidth() / 2 - 200, 1500));
        ImGui::Begin("Temp Window");
        ImGui::DragFloat("camera zoom", &zoom, 0.1f, 0.1f, 100.0f, NULL, 1.f);
        ImGui::End();

        //DEMO WINDOW
        // static bool show = true;
        // ImGui::ShowDemoWindow(&show);
    }

    void DawnEditor::onClose()
    {
    }

}  // namespace Dawn