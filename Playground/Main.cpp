#include "Dawn/Dawn.h"

class Playground : public Dawn::Application
{
   public:
    Dawn::Texture tex1;
    Dawn::Texture tex2;

    Dawn::Entity parentsParent;
    Dawn::Entity parent;

    Dawn::Scene scene = Dawn::Scene();

    Playground()
    {
        const float aspectRatio = 1920 / 1920;
        const float zoom = 10.0f;
        scene.getMainCamera()->setProjection(-aspectRatio * zoom, aspectRatio * zoom, -1.0 * zoom, 1.0 * zoom);

        tex1.loadFromFile("test.png");
        tex2.loadFromFile("test2.png");

        parentsParent = scene.addEntity();
        scene.addComponent<Dawn::TransformComponent>(parentsParent);
        scene.addComponent<Dawn::SpriteRendererComponent>(parentsParent);
        auto& parentsParentSprite = scene.getComponent<Dawn::SpriteRendererComponent>(parentsParent);
        parentsParentSprite.texture = &tex2;

        parent = scene.addEntity();
        scene.addComponent<Dawn::TransformComponent>(parent);
        scene.addComponent<Dawn::ParentComponent>(parent);
        scene.addComponent<Dawn::SpriteRendererComponent>(parent);
        auto& parentSprite = scene.getComponent<Dawn::SpriteRendererComponent>(parent);
        parentSprite.texture = &tex1;

        scene.makeEntityChild(parent, parentsParent);

        for (int i = 0; i < 10; i++) {
            Dawn::Entity e = scene.addEntity();

            scene.addComponent<Dawn::TransformComponent>(e);
            auto& transform = scene.getComponent<Dawn::TransformComponent>(e);
            transform.position = Dawn::Vec3(i, 0, 0);
            transform.scale = Dawn::Vec3(0.5);
            transform.rotation = i;

            scene.addComponent<Dawn::SpriteRendererComponent>(e);
            auto& spriteRenderer = scene.getComponent<Dawn::SpriteRendererComponent>(e);
            spriteRenderer.color = Dawn::Vec4(0.5, 0.6, 0.2, 1);

            scene.makeEntityChild(e, parent);
        }

        // int quads = 0;
        // for (float x = -1.0; x < 1.0; x += 0.02) {
        //     for (float y = -1.0; y < 1.0; y += 0.02) {
        //         quads++;
        //         Dawn::Texture* tex = nullptr;
        //         if (quads % 2 == 0)
        //             tex = &tex1;
        //         else {
        //             tex = &tex2;
        //         }

        //         Dawn::Entity e = scene.addEntity();

        //         scene.addComponent<Dawn::TransformComponent>(e);
        //         auto& transform = scene.getComponent<Dawn::TransformComponent>(e);
        //         transform.position = Dawn::Vec3(x, y, 0);
        //         transform.scale = Dawn::Vec3(.02, .02, 1.0);

        //         scene.addComponent<Dawn::SpriteRendererComponent>(e);
        //         auto& spriteRenderer = scene.getComponent<Dawn::SpriteRendererComponent>(e);
        //         spriteRenderer.texture = tex;
        //         spriteRenderer.color = Dawn::Vec4((x + 1) / 2, (y + 1) / 2, 1.0, 1.0);
        //     }
        // }

        // DAWN_LOG(quads);
    }

    void onUpdate() override
    {
        DAWN_PROFILE_FUNC();

        if (Dawn::Input::GetKeyDown(Dawn::KeyCode::B)) {
            DAWN_LOG("B is being pressed");
        }
        if (Dawn::Input::GetMouseButtonDown(Dawn::MouseCode::Middle)) {
            DAWN_LOG("Middle MB being pressed");
        }

        scene.onUpdate();
    }

    void onClose() override
    {
    }
};

int main()
{
    Playground playground = Playground();
    playground.start();

    return 0;
}