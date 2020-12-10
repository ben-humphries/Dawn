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

            for (auto& e : m_registry->getAllEntitiesSet()) {
                auto entityBitset = m_registry->getEntityBitset(e);
                if (entityBitsetMatch(entityBitset, this->m_entityBitset)) {
                    this->m_entities.insert(e);
                } else {
                    this->m_entities.erase(e);
                }
            }
        };

       private:
        bool entityBitsetMatch(std::vector<bool>& entityBitset, std::vector<bool>& systemBitset)
        {
            for (int i = 0; i < systemBitset.size(); i++) {
                if (systemBitset[i] && !entityBitset[i])
                    return false;
            }

            return true;
        }
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

        void entityBitsetChanged(Entity e)
        {
            for (auto system : m_systems) {
                auto entityBitset = system->m_registry->getEntityBitset(e);
                if (entityBitsetMatch(entityBitset, system->m_entityBitset)) {
                    system->m_entities.insert(e);
                } else {
                    system->m_entities.erase(e);
                }
            }
        }

       private:
        bool entityBitsetMatch(std::vector<bool>& entityBitset, std::vector<bool>& systemBitset)
        {
            for (int i = 0; i < systemBitset.size(); i++) {
                if (systemBitset[i] && !entityBitset[i])
                    return false;
            }

            return true;
        }

       private:
        std::vector<BaseSystem*> m_systems;
    };
}  // namespace Dawn