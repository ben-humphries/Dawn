#pragma once

#include "Math/Math.h"

namespace Dawn
{
    class Renderer2D
    {
       public:
        static void Init();
        static void Terminate();

        static void StartFrame();
        static void EndFrame();

        static void DrawQuad(Vec3 position, Vec4 color);
    };
}