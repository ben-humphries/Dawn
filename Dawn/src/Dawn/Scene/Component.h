#pragma once
#include "DawnPCH.h"

#include "ECS/ECSComponent.h"

namespace Dawn
{
    struct TransformComponent : public Component<TransformComponent> {
        float pos;
        float rotation;
        float scale;
    };

    struct RenderComponent : public Component<RenderComponent> {
        int render;
        std::string test = "testing initialization";
    };
}