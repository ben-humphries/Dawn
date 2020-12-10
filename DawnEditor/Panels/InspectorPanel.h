#pragma once
#include "Dawn/Dawn.h"
#include "DawnPCH.h"

namespace Dawn
{
    class InspectorPanel
    {
       public:
        InspectorPanel(Scene* scene);

        void draw(Entity selectedEntity);

       private:
       private:
        Scene* m_activeScene;
    };
}  // namespace Dawn