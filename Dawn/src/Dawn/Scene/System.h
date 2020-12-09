#pragma once
#include "DawnPCH.h"

#include "ECS/ECSSystem.h"

#include "Render/Renderer2D.h"

//TODO: Clean up the initializers for these classes. There is probably a way not to require them here.
//The API around systems is a little dodgy in general.

namespace Dawn
{
    class RenderSystem : public System<TransformComponent, SpriteRendererComponent>
    {
       public:
        RenderSystem(EntityRegistry* registry)
            : System(registry){};
        void onUpdate()
        {
            for (auto e : m_entities) {
                auto& transform = m_registry->getComponent<TransformComponent>(e);
                auto& spriteRenderer = m_registry->getComponent<SpriteRendererComponent>(e);
                Renderer2D::DrawQuad(transform.position, transform.rotation, transform.scale, spriteRenderer.color, spriteRenderer.texture);
            }
        }
    };

    class CameraSystem : public System<CameraComponent>
    {
       public:
        CameraSystem(EntityRegistry* registry)
            : System(registry){};

        OrthographicCamera* getMainCamera()
        {
            for (auto e : m_entities) {
                auto& cameraComponent = m_registry->getComponent<CameraComponent>(e);
                if (cameraComponent.primary)
                    return cameraComponent.camera;
            }
        }
    };

    //This may need to be changed as the order that the entities are iterated through matters. Nested children need to be updated first
    class ParentChildSystem : public System<ChildComponent, TransformComponent>
    {
       public:
        ParentChildSystem(EntityRegistry* registry)
            : System(registry){};

        void onUpdate()
        {
            for (auto e : m_entities) {
                auto& childComponent = m_registry->getComponent<ChildComponent>(e);

                if (!m_registry->hasComponent<TransformComponent>(childComponent.parent))
                    return;

                auto& transform = m_registry->getComponent<TransformComponent>(e);
                auto& parentTransform = m_registry->getComponent<TransformComponent>(childComponent.parent);

                transform.position = parentTransform.position + childComponent.localPosition;
                transform.rotation = parentTransform.rotation + childComponent.localRotation;
                transform.scale = parentTransform.scale * childComponent.localScale;
            }
        }
    };
};