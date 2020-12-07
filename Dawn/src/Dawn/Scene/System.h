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
};