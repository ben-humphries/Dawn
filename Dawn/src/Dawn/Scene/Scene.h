#pragma once
#include "DawnPCH.h"
#include "ECS/ECSEntity.h"
#include "ECS/ECSSystem.h"
#include "Render/Camera.h"
#include "System.h"

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
            Entity e = m_registry.addEntity();
            m_registry.addComponent<TagComponent>(e);
            return e;
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

        void makeEntityChild(Entity e, Entity parent)
        {
            //If parent is null, remove child.
            if (!parent) {
                if (hasComponent<ChildComponent>(e))
                    deleteComponent<ChildComponent>(e);
            }

            if (!hasComponent<ParentComponent>(parent))
                addComponent<ParentComponent>(parent);
            auto& parentComponent = getComponent<ParentComponent>(parent);
            parentComponent.children.push_back(e);

            if (!hasComponent<ChildComponent>(e))
                addComponent<ChildComponent>(e);
            auto& childComponent = getComponent<ChildComponent>(e);
            childComponent.parent = parent;
        }

        template <class T>
        void addComponent(Entity e)
        {
            m_registry.addComponent<T>(e);
            m_systemRegistry.entityBitsetChanged(e);
        }

        template <class T>
        void deleteComponent(Entity e)
        {
            m_registry.deleteComponent<T>(e);
            m_systemRegistry.entityBitsetChanged(e);
        }

        template <class T>
        T& getComponent(Entity e)
        {
            return m_registry.getComponent<T>(e);
        }

        template <class T>
        bool hasComponent(Entity e)
        {
            return m_registry.hasComponent<T>(e);
        }

        EntityRegistry* getRegistry()
        {
            return &m_registry;
        }

       private:
        EntityRegistry m_registry;
        SystemRegistry m_systemRegistry;

        RenderSystem* m_renderSystem;
        CameraSystem* m_cameraSystem;
    };
}  // namespace Dawn