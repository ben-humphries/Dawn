#include "InspectorPanel.h"

//Debug
#include "Debug/ImGuiDebug.h"

namespace Dawn
{
    InspectorPanel::InspectorPanel(Scene *scene)
        : m_activeScene(scene){};

    template <class T>
    void drawAddComponentMenuItem(const std::string &name, Scene *scene, Entity e)
    {
        if (!scene->hasComponent<T>(e)) {
            if (ImGui::MenuItem(name.c_str())) {
                scene->addComponent<T>(e);
            }
        }
    }

    template <class T, class Function>
    void drawComponent(const std::string &name, Scene *scene, Entity e, Function func, bool deletable = true)
    {
        if (!scene->hasComponent<T>(e))
            return;

        bool deleted = false, reset = false;

        auto &component = scene->getComponent<T>(e);

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow |
                                   ImGuiTreeNodeFlags_OpenOnDoubleClick |
                                   ImGuiTreeNodeFlags_SpanAvailWidth |
                                   ImGuiTreeNodeFlags_AllowItemOverlap |
                                   ImGuiTreeNodeFlags_Selected;

        ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(.5f, .5f, .5f, .8f));

        ImGui::SetNextTreeNodeOpen(true, ImGuiCond_FirstUseEver);
        bool open = ImGui::TreeNodeEx(name.c_str(), flags);

        ImGuiStyle &style = ImGui::GetStyle();

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));

        //TODO: Eventually make this an image
        ImGui::SameLine(ImGui::GetContentRegionAvail().x);
        if (ImGui::Button("...", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetFontSize()))) {
            ImGui::OpenPopup("ComponentActionList");
        }

        if (ImGui::BeginPopup("ComponentActionList")) {
            reset = ImGui::MenuItem("Reset Component");
            if (deletable)
                deleted = ImGui::MenuItem("Delete Component");
            ImGui::EndPopup();
        }

        ImGui::PopStyleVar();

        if (open) {
            ImGui::Separator();
            func(component);
            ImGui::Separator();

            ImGui::TreePop();
        }

        ImGui::PopStyleColor();

        if (reset)
            component = T();
        if (deleted)
            scene->deleteComponent<T>(e);
    }

    void InspectorPanel::draw(Entity selectedEntity)
    {
        ImGui::Begin("Inspector Panel", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
        if (selectedEntity) {
            ImGui::Text(m_activeScene->getComponent<TagComponent>(selectedEntity).tag.c_str());

            drawComponent<TagComponent>(
                "Tag Component", m_activeScene, selectedEntity, [](auto &component) {
                    char buffer[128];
                    memset(buffer, 0, sizeof(buffer));
                    memcpy(buffer, component.tag.c_str(), sizeof(buffer));

                    ImGui::Text("Tag: ");
                    ImGui::SameLine();
                    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
                    if (ImGui::InputText("##taginput", buffer, sizeof(buffer))) {
                        component.tag = std::string(buffer);
                    }
                },
                false);

            drawComponent<TransformComponent>(
                "Transform Component", m_activeScene, selectedEntity, [](auto &component) {
                    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6, 6));

                    ImGui::Text("Position: ");
                    ImGui::SameLine();
                    ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
                    ImGui::DragFloat3("#position", (float *)&component.position, 0.1f, -100.0f, 100.0f, "%.4f", 1.f);
                    ImGui::PopItemWidth();

                    ImGui::Separator();

                    ImGui::Text("Rotation: ");
                    ImGui::SameLine();
                    ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
                    ImGui::DragFloat("#rotation", &component.rotation, 0.1f, 0.f, 6.28f, "%.4f", 1.f);
                    ImGui::PopItemWidth();

                    ImGui::Separator();

                    ImGui::Text("Scale:    ");
                    ImGui::SameLine();
                    ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
                    ImGui::DragFloat3("#scale", (float *)&component.scale, 0.1f, -100.0f, 100.0f, "%.4f", 1.f);
                    ImGui::PopItemWidth();

                    ImGui::PopStyleVar();
                });

            drawComponent<SpriteRendererComponent>(
                "Sprite Renderer Component", m_activeScene, selectedEntity, [](auto &component) {
                    ImGui::Text("Sprite Color: ");
                    ImGui::SameLine();
                    ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB;
                    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
                    ImGui::ColorPicker4("##spritecolor", (float *)&component.color, flags);
                });

            drawComponent<CameraComponent>(
                "Camera Component", m_activeScene, selectedEntity, [](auto &component) {
                    ImGui::Text("Primary: ");
                    ImGui::SameLine();
                    ImGui::Checkbox("##primary", &component.primary);
                });

            //Add Component
            if (ImGui::Button("+", ImVec2(ImGui::GetContentRegionAvail().x, 35))) {
                ImGui::OpenPopup("AddComponentList");
            }

            if (ImGui::BeginPopup("AddComponentList")) {
                drawAddComponentMenuItem<TransformComponent>("Transform Component", m_activeScene, selectedEntity);
                drawAddComponentMenuItem<SpriteRendererComponent>("Sprite Renderer Component", m_activeScene, selectedEntity);
                drawAddComponentMenuItem<CameraComponent>("Camera Component", m_activeScene, selectedEntity);
                ImGui::EndPopup();
            }
        }
        ImGui::End();
    }
}  // namespace Dawn