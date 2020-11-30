#pragma once
#include "DawnPCH.h"

#include "Math/Math.h"
#include "Texture.h"

namespace Dawn
{
    class Renderer2D
    {
       public:
        static void Init();
        static void Terminate();

        static void StartFrame();
        static void Flush();
        static void EndFrame();

        static void DrawQuad(Vec3 position, float rotation, Vec3 scale, Vec4 color, Texture* texture = nullptr);
    };
}