#include "SceneHierarchyPanel.h"

namespace Dawn
{
    SceneHierarchyPanel::SceneHierarchyPanel(Scene* scene)
        : m_activeScene(scene){};

    void SceneHierarchyPanel::draw()
    {
        ImGui::Begin("Scene Hierarchy Panel", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);

        std::set<Entity> entities = m_activeScene->getRegistry()->getAllEntitiesSet();

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
        bool hasChildren = m_activeScene->hasComponent<ParentComponent>(e);

        if (draw) {
            ImGui::SetNextTreeNodeOpen(hasChildren, ImGuiCond_FirstUseEver);
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