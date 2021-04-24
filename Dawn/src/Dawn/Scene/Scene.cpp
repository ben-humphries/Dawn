#include "Scene.h"

#include "Component.h"
#include "Render/Renderer2D.h"
#include "System.h"

namespace Dawn
{
    void Scene::onWindowResize(const Event& e)
    {
        const WindowResizedEvent& w_e = (const WindowResizedEvent&)e;

        const float aspectRatio = ((float)w_e.getWidth()) / ((float)w_e.getHeight());
        getMainCamera()->setAspectRatio(aspectRatio);
    }

    Scene::Scene(float aspectRatio)
    {
        //Add main camera
        Entity mainCamera = addEntity();
        addComponent<CameraComponent>(mainCamera);
        auto& cameraComponent = getComponent<CameraComponent>(mainCamera);
        cameraComponent.camera = new Dawn::OrthographicCamera(aspectRatio, 1.0);
        cameraComponent.camera->setPosition(Vec3(0, 0, -1));
        cameraComponent.primary = true;

        //Initialize systems
        m_renderSystem = m_systemRegistry.addSystem<RenderSystem>(&m_registry);
        m_cameraSystem = m_systemRegistry.addSystem<CameraSystem>(&m_registry);

        EventHandler::Listen(EventType::WindowResized, BIND_EVENT_MEMBER_FN(Scene::onWindowResize));
    }

    void Scene::onUpdate()
    {
        PROFILE_FUNC();

        OrthographicCamera* mainCamera = m_cameraSystem->getMainCamera();

        m_cameraSystem->onUpdate();

        if (mainCamera) {
            //These Renderer2D functions could be contained within RenderSystem
            Renderer2D::StartFrame(*mainCamera);

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