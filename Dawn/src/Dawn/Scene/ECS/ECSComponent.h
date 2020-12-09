#pragma once
#include "DawnPCH.h"

namespace Dawn
{
    extern uint32_t currentComponentId;

    struct BaseComponent {
        static uint32_t nextId();

        static uint32_t maxId();
    };

    template <class T>
    struct Component : public BaseComponent {
        static const uint32_t s_id;
    };

    template <typename T>
    const uint32_t Component<T>::s_id(BaseComponent::nextId());
}  // namespace Dawn