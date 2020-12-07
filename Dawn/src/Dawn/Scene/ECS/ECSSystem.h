#pragma once
#include "DawnPCH.h"

#include "ECSEntity.h"

namespace Dawn
{
    class BaseSystem
    {
       public:
        BaseSystem(EntityRegistry* registry)
            : m_registry(registry), m_entityBitset(std::vector<bool>(BaseComponent::maxId())){};
        void updateEntityList()
        {
            m_entities = m_registry->getEntitiesWithBitset(m_entityBitset);
        }

       protected:
        EntityRegistry* m_registry;

        std::set<Entity> m_entities;
        std::vector<bool> m_entityBitset;

        friend class SystemRegistry;
    };

    template <class... T>
    class System : public BaseSystem
    {
       public:
        System(EntityRegistry* registry)
            : BaseSystem(registry)
        {
            std::vector<uint32_t> componentIds = {T::s_id...};

            for (auto id : componentIds) {
                m_entityBitset[id] = true;
            }

            updateEntityList();
        };
    };

    class SystemRegistry
    {
       public:
        template <class T>
        T* addSystem(EntityRegistry* registry)
        {
            BaseSystem* newSystem = new T(registry);
            m_systems.push_back(newSystem);

            return (T*)newSystem;
        }

        void entityDeleted(Entity e)
        {
            for (auto system : m_systems) {
                system->m_entities.erase(e);
            }
        }

        void entityBitsetChanged(Entity e, std::vector<bool> entityBitset)
        {
            for (auto system : m_systems) {
                if (system->m_entityBitset == entityBitset) {
                    system->m_entities.insert(e);
                } else {
                    system->m_entities.erase(e);
                }
            }
        }

       private:
        std::vector<BaseSystem*> m_systems;
    };
}