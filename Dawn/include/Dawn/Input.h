#pragma once

#include "Dawn/KeyCode.h"
#include "Dawn/MouseCode.h"

namespace Dawn
{
    class Input
    {
       public:
        static bool GetKeyDown(KeyCode key);
        static bool GetMouseButtonDown(MouseCode button);

        //TODO: Implement mouse position function, once we have a vector type.
    };
}