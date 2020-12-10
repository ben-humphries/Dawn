#pragma once
#include "Dawn/Dawn.h"
#include "DawnPCH.h"

namespace Dawn
{
    class SceneHierarchyPanel
    {
       public:
        SceneHierarchyPanel(Scene* scene);

        void drawPanel();

       private:
        void drawEntityTreeNode(Entity e, std::set<Entity>& entitySet, bool draw = true);

       private:
        Scene* m_activeScene;
        Entity m_selectedEntity = 0;
    };
}  // namespace Dawn