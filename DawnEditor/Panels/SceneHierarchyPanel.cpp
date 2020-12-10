#include "SceneHierarchyPanel.h"

namespace Dawn
{
    SceneHierarchyPanel::SceneHierarchyPanel(Scene* scene)
        : m_activeScene(scene){};

    void SceneHierarchyPanel::drawPanel()
    {
        ImGui::Begin("Scene Hierarchy Panel");

        std::set<Entity> entities = m_activeScene->getRegistry()->getAllEntitiesSet();
        // for (auto& e : m_activeScene->getRegistry()->getAllEntitiesSet()) {
        //     drawEntityTreeNode(e);
        // }

        auto it = entities.begin();
        while (it != entities.end()) {
            drawEntityTreeNode(*it, entities);
            it = entities.begin();
        }

        ImGui::End();
    }

    void SceneHierarchyPanel::drawEntityTreeNode(Entity e, std::set<Entity>& entitySet, bool draw)
    {
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

        if (m_selectedEntity == e)
            flags |= ImGuiTreeNodeFlags_Selected;

        bool open;

        if (draw) {
            open = ImGui::TreeNodeEx((void*)e, flags, m_activeScene->getComponent<TagComponent>(e).tag.c_str());
            if (ImGui::IsItemClicked()) {
                m_selectedEntity = e;
            }
        }

        if (m_activeScene->hasComponent<ParentComponent>(e)) {
            auto& parentComponent = m_activeScene->getComponent<ParentComponent>(e);
            for (auto child : parentComponent.children) {
                drawEntityTreeNode(child, entitySet, open);
            }
        }
        if (open)
            ImGui::TreePop();

        entitySet.erase(e);
    }

}  // namespace Dawn