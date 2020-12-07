#pragma once
#include "DawnPCH.h"

namespace Dawn
{
    static uint32_t currentComponentId = 0;
    struct BaseComponent {
        static uint32_t nextId()
        {
            return currentComponentId++;
        }

        static uint32_t maxId()
        {
            return currentComponentId;
        }
    };

    template <class T>
    struct Component : public BaseComponent {
        static const uint32_t s_id;
    };

    template <typename T>
    const uint32_t Component<T>::s_id(BaseComponent::nextId());
}  // namespace Dawn