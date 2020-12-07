#pragma once
#include "DawnPCH.h"
#include "ECS/ECSEntity.h"
#include "Render/Camera.h"

namespace Dawn
{
    class Scene
    {
       public:
        Scene();

        void onUpdate();

        OrthographicCamera* getMainCamera();

        //TODO: There is probably a better API than this to allow entities to be added/modified from outside of this class.
        EntityRegistry& getRegistry()
        {
            return m_registry;
        }

       private:
        EntityRegistry m_registry;
    };
}  // namespace Dawn