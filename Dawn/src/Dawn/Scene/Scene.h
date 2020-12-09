#pragma once
#include "DawnPCH.h"
#include "ECS/ECSEntity.h"
#include "ECS/ECSSystem.h"
#include "System.h"
#include "Render/Camera.h"

namespace Dawn
{
    class Scene
    {
       public:
        Scene();

        void onUpdate();

        OrthographicCamera* getMainCamera();

        Entity addEntity()
        {
            return m_registry.addEntity();
        }
        void deleteEntity(Entity e)
        {
            //If entity has Parent component, loop through children and remove the child component from them.
            if (m_registry.hasComponent<ParentComponent>(e)) {
                auto& parentComponent = m_registry.getComponent<ParentComponent>(e);

                for (auto& child : parentComponent.children) {
                    deleteComponent<ChildComponent>(child);
                }
            }

            m_registry.deleteEntity(e);
            m_systemRegistry.entityDeleted(e);
        }
        template <class T>
        void addComponent(Entity e)
        {
            m_registry.addComponent<T>(e);
            m_systemRegistry.entityBitsetChanged(e, m_registry.getEntityBitset(e));
        }
        template <class T>
        void deleteComponent(Entity e)
        {
            m_registry.deleteComponent<T>(e);
            m_systemRegistry.entityBitsetChanged(e, m_registry.getEntityBitset(e));
        }

        template <class T>
        T& getComponent(Entity e)
        {
            return m_registry.getComponent<T>(e);
        }

       private:
        EntityRegistry m_registry;
        SystemRegistry m_systemRegistry;

        RenderSystem* m_renderSystem;
        CameraSystem* m_cameraSystem;
    };
}  // namespace Dawn