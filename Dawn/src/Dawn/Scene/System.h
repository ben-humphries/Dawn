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

                const Vec3 axis = Vec3(0, 0, 1);

                Mat4 modelMatrix = GetModelMatrix(
                    GetTranslationMatrix(transform.position),
                    GetRotationMatrix(axis, transform.rotation),
                    GetScaleMatrix(transform.scale));

                Entity current = e;

                //If there is a child component, apply transformations relative to its transform before submitting to the renderer
                //TODO: these should probably eventually be localToWorld() functions or something like that so they can be used in collision and stuff later
                while (m_registry->hasComponent<ChildComponent>(current)) {
                    auto& childComponent = m_registry->getComponent<ChildComponent>(current);
                    if (m_registry->hasComponent<TransformComponent>(childComponent.parent)) {
                        auto& parentTransform = m_registry->getComponent<TransformComponent>(childComponent.parent);

                        modelMatrix = GetModelMatrix(GetTranslationMatrix(parentTransform.position),
                                                     GetRotationMatrix(axis, parentTransform.rotation),
                                                     GetScaleMatrix(parentTransform.scale)) *
                                      modelMatrix;
                    }
                    current = childComponent.parent;
                }

                Renderer2D::DrawQuad(modelMatrix, spriteRenderer.color, spriteRenderer.texture);
            }
        }
    };

    class CameraSystem : public System<CameraComponent>
    {
       public:
        CameraSystem(EntityRegistry* registry)
            : System(registry){};

        void onUpdate()
        {
            for (auto e : m_entities) {
                if (m_registry->hasComponent<TransformComponent>(e)) {
                    auto& transformComponent = m_registry->getComponent<TransformComponent>(e);
                    auto& cameraComponent = m_registry->getComponent<CameraComponent>(e);

                    cameraComponent.camera->setPosition(transformComponent.position);
                    cameraComponent.camera->setRotation(transformComponent.rotation);
                }
            }
        }

        OrthographicCamera* getMainCamera()
        {
            for (auto e : m_entities) {
                auto& cameraComponent = m_registry->getComponent<CameraComponent>(e);
                if (cameraComponent.primary)
                    return cameraComponent.camera;
            }

            return nullptr;
        }
    };
};  // namespace Dawn