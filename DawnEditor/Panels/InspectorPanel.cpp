#include "InspectorPanel.h"

namespace Dawn
{
    InspectorPanel::InspectorPanel(Scene *scene)
        : m_activeScene(scene){};

    void InspectorPanel::draw(Entity selectedEntity)
    {
        ImGui::Begin("Inspector Panel", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
        if (selectedEntity) {
            ImGui::Text(m_activeScene->getComponent<TagComponent>(selectedEntity).tag.c_str());

            if (m_activeScene->hasComponent<TransformComponent>(selectedEntity)) {
                auto &transform = m_activeScene->getComponent<TransformComponent>(selectedEntity);

                ImGui::Separator();

                ImGui::Text("Position: ");
                ImGui::SameLine();
                ImGui::DragFloat3("", (float *)&transform.position, 0.1f, -100.0f, 100.0f, NULL, 1.f);

                ImGui::Separator();

                ImGui::Text("Rotation: ");
                ImGui::SameLine();
                ImGui::DragFloat("", &transform.rotation, 0.1f, 0.f, 6.28f, NULL, 1.f);

                ImGui::Separator();

                ImGui::Text("Scale:    ");
                ImGui::SameLine();
                ImGui::DragFloat3("", (float *)&transform.scale, 0.1f, -100.0f, 100.0f, NULL, 1.f);
            }
        }
        ImGui::End();
    }
}  // namespace Dawn