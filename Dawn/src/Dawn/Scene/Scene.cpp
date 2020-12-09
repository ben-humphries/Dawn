#include "Scene.h"

#include "Component.h"
#include "Render/Renderer2D.h"
#include "System.h"

namespace Dawn
{
    Scene::Scene()
    {
        //Add main camera
        Entity mainCamera = addEntity();
        addComponent<CameraComponent>(mainCamera);
        auto& cameraComponent = getComponent<CameraComponent>(mainCamera);
        cameraComponent.camera = new Dawn::OrthographicCamera(-1.0, 1.0, -0.5, 0.5);
        cameraComponent.camera->setPosition(Vec3(0, 0, -1));
        cameraComponent.primary = true;

        //Initialize systems
        m_renderSystem = m_systemRegistry.addSystem<RenderSystem>(&m_registry);
        m_cameraSystem = m_systemRegistry.addSystem<CameraSystem>(&m_registry);
        m_parentChildSystem = m_systemRegistry.addSystem<ParentChildSystem>(&m_registry);
    }

    void Scene::onUpdate()
    {
        PROFILE_FUNC();

        OrthographicCamera* mainCamera = m_cameraSystem->getMainCamera();

        if (mainCamera) {
            //These Renderer2D functions could be contained within RenderSystem
            Renderer2D::StartFrame(*mainCamera);

            m_parentChildSystem->onUpdate();
            m_renderSystem->onUpdate();

            Renderer2D::EndFrame();
        }
    }

    OrthographicCamera* Scene::getMainCamera()
    {
        PROFILE_FUNC();
        return m_cameraSystem->getMainCamera();
    }
}  // namespace Dawn