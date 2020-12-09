#include "ECSComponent.h"

namespace Dawn
{
    uint32_t currentComponentId = 0;

    uint32_t BaseComponent::nextId()
    {
        return currentComponentId++;
    }

    uint32_t BaseComponent::maxId()
    {
        return currentComponentId;
    }
}  // namespace Dawn