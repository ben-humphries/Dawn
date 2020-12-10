#pragma once
#include "DawnPCH.h"
#include "ECS/ECSComponent.h"
#include "Math/Math.h"
#include "Render/Camera.h"
#include "Render/Texture.h"

namespace Dawn
{
    typedef uint32_t Entity;

    struct TagComponent : public Component<TagComponent> {
        std::string tag = "Entity";
    };

    struct TransformComponent : public Component<TransformComponent> {
        Vec3 position = Vec3(0.0f, 0.0f, 0.0f);
        float rotation = 0.0f;
        Vec3 scale = Vec3(1.0f, 1.0f, 1.0f);
    };

    struct SpriteRendererComponent : public Component<SpriteRendererComponent> {
        Texture* texture = nullptr;
        Vec4 color = Vec4(1, 1, 1, 1);
        //TODO: material
    };

    struct CameraComponent : public Component<CameraComponent> {
        OrthographicCamera* camera = nullptr;
        bool primary = false;
    };

    struct ParentComponent : public Component<ParentComponent> {
        std::vector<Entity> children;
    };

    struct ChildComponent : public Component<ChildComponent> {
        Entity parent;
    };
}  // namespace Dawn