#include "Scene.h"

#include "Component.h"
#include "Render/Renderer2D.h"

//Temp
#include "Core/Log.h"

namespace Dawn
{
    Scene::Scene()
    {
        Entity mainCamera = m_registry.addEntity();
        m_registry.addComponent<CameraComponent>(mainCamera);
        auto& cameraComponent = m_registry.getComponent<CameraComponent>(mainCamera);
        cameraComponent.camera = new Dawn::OrthographicCamera(-1.0, 1.0, -0.5, 0.5);
        cameraComponent.camera->setPosition(Vec3(0, 0, -1));
        cameraComponent.primary = true;
    }

    void Scene::onUpdate()
    {
        OrthographicCamera* mainCamera = getMainCamera();

        if (mainCamera) {
            Renderer2D::StartFrame(*mainCamera);

            for (auto entity : m_registry.getEntitiesWithComponents<TransformComponent, SpriteRendererComponent>()) {
                auto& transform = m_registry.getComponent<TransformComponent>(entity);
                auto& spriteRenderer = m_registry.getComponent<SpriteRendererComponent>(entity);

                Renderer2D::DrawQuad(transform.position, transform.rotation, transform.scale, spriteRenderer.color, spriteRenderer.texture);
            }

            Renderer2D::EndFrame();
        }
    }

    OrthographicCamera* Scene::getMainCamera()
    {
        OrthographicCamera* mainCamera = nullptr;

        for (auto entity : m_registry.getEntitiesWithComponents<CameraComponent>()) {
            auto& cameraComponent = m_registry.getComponent<CameraComponent>(entity);
            if (cameraComponent.primary) {
                mainCamera = cameraComponent.camera;
            }
        }

        return mainCamera;
    }
}  // namespace Dawn