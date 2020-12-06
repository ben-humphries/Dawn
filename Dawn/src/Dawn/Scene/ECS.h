#pragma once
#include "DawnPCH.h"

namespace Dawn
{
    typedef uint32_t Entity;

    static uint32_t currentComponentId = 1;
    struct BaseComponent {
        static uint32_t nextId()
        {
            return currentComponentId++;
        }
    };

    template <class T>
    struct Component : public BaseComponent {
        static const uint32_t s_id;
    };

    template <typename T>
    const uint32_t Component<T>::s_id(BaseComponent::nextId());

    struct TransformComponent : public Component<TransformComponent> {
        float pos;
        float rotation;
        float scale;
    };

    struct RenderComponent : public Component<RenderComponent> {
        int render;
        std::string test = "testing initialization";
    };

    class EntityRegistry
    {
       public:
        template <class T>
        void addComponent(Entity e)
        {
            int index = T::s_id;

            while (index >= m_componentLists.size()) {
                std::vector<BaseComponent*> newVec;
                for (int i = 0; i < m_nextEntity; i++) {
                    newVec.push_back(nullptr);
                }
                m_componentLists.push_back(newVec);
            }

            m_componentLists[index][e] = new T();
        }

        template <class T>
        T& getComponent(Entity e)
        {
            int componentListIndex = T::s_id;
            int componentIndex = m_entityIndexMap.at(e);
            return (T&)*m_componentLists[componentListIndex][componentIndex];
        }

        Entity addEntity()
        {
            Entity nextEntity;
            if (m_deletedEntities.size() > 0) {
                nextEntity = m_deletedEntities.front();
                m_deletedEntities.pop();
            } else {
                nextEntity = m_nextEntity++;
            }
            m_entityIndexMap.emplace(nextEntity, m_entityIndexMap.size() + 1);
            return nextEntity;
        }

        void deleteEntity(Entity e)
        {
            //Check if entity has these components first with bitbuffer
            for (auto& componentList : m_componentLists) {
                delete componentList[e];
                componentList[e] = componentList[m_nextEntity - 1];  // copy last component pointer into current index
                componentList[m_nextEntity - 1] = nullptr;
            }

            m_entityIndexMap.erase(e);
            m_entityIndexMap[m_nextEntity - 1] = e;

            m_deletedEntities.push(e);
        }

       private:
        std::vector<std::vector<BaseComponent*> > m_componentLists;
        std::unordered_map<Entity, uint32_t> m_entityIndexMap;

        std::queue<Entity> m_deletedEntities;

        Entity m_nextEntity = 1;
    };
}