#pragma once
#include "DawnPCH.h"
#include "ECSComponent.h"
#include "Scene/Component.h"

//DEBUG
#include "Debug/Profile.h"

namespace Dawn
{
    typedef uint32_t Entity;

    class EntityRegistry
    {
       public:
        EntityRegistry()
            : m_componentLists(BaseComponent::maxId()), m_entityIndexMaps(BaseComponent::maxId())
        {
        }

        template <class T>
        void addComponent(Entity e)
        {
            int index = T::s_id;

            //Can't add duplicate components
            if (m_entityBitsets[e].size() > index && m_entityBitsets[e][index])
                return;

            m_componentLists[index].push_back(new T());

            m_entityIndexMaps[index].emplace(e, m_componentLists[index].size() - 1);

            m_entityBitsets[e][index] = true;
        }

        template <class T>
        bool hasComponent(Entity e)
        {
            int index = T::s_id;
            return hasComponentInternal(index, e);
        }

        template <class T>
        T& getComponent(Entity e)
        {
            int componentListIndex = T::s_id;
            int componentIndex = m_entityIndexMaps[componentListIndex].at(e);
            return (T&)*m_componentLists[componentListIndex][componentIndex];
        }

        template <class T>
        void deleteComponent(Entity e)
        {
            int index = T::s_id;
            deleteComponentInternal(index, e);
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

            m_entityBitsets.emplace(nextEntity, std::vector<bool>(BaseComponent::maxId()));

            return nextEntity;
        }

        void deleteEntity(Entity e)
        {
            if (!entityExists(e)) return;

            for (int i = 0; i < BaseComponent::maxId(); i++) {
                deleteComponentInternal(i, e);
            }

            m_deletedEntities.push(e);

            m_entityBitsets.erase(e);
        }

        bool entityExists(Entity e)
        {
            auto it = m_entityBitsets.find(e);

            return (it != m_entityBitsets.end());
        }

        //Note: this function does not guarantee that entities are returned in the order they were added.
        template <class... T>
        std::vector<Entity> getEntitiesWithComponents()
        {
            PROFILE_FUNC();
            std::vector<uint32_t> componentIds = {T::s_id...};

            std::vector<Entity> entities;

            for (auto it : m_entityBitsets) {
                const Entity e = it.first;
                bool shouldAdd = true;
                for (auto& componentId : componentIds) {
                    if (!hasComponentInternal(componentId, e)) shouldAdd = false;
                }

                if (shouldAdd) entities.push_back(e);
            }
            return entities;
        }

        std::set<Entity> getEntitiesWithBitset(std::vector<bool> entityBitset)
        {
            std::set<Entity> entities;

            for (auto it : m_entityBitsets) {
                if (it.second == entityBitset)
                    entities.insert(it.first);
            }
            return entities;
        }

        template <class T>
        std::vector<T*> getComponentsOfType()
        {
            PROFILE_FUNC();

            int index = T::s_id;
            std::vector<T*> components;

            for (auto componentPtr : m_componentLists[index]) {
                components.push_back((T*)componentPtr);
            }
            return components;
        }

        std::vector<bool> getEntityBitset(Entity e)
        {
            return m_entityBitsets[e];
        }

       private:
        void deleteComponentInternal(int componentId, Entity e)
        {
            auto& componentList = m_componentLists[componentId];

            //Check that component exists before we delete it
            if (hasComponentInternal(componentId, e)) {
                int componentIndex = m_entityIndexMaps[componentId].at(e);

                delete componentList[componentIndex];

                componentList[componentIndex] = componentList[componentList.size() - 1];  // copy last component pointer into current index
                componentList.pop_back();

                m_entityIndexMaps[componentId].erase(e);
                m_entityBitsets[e][componentId] = false;
            }
        }

        bool hasComponentInternal(int componentId, Entity e)
        {
            return m_entityBitsets[e][componentId];
        }

       private:
        std::vector<std::vector<BaseComponent*>> m_componentLists;
        std::vector<std::unordered_map<Entity, uint32_t>> m_entityIndexMaps;
        std::queue<Entity> m_deletedEntities;
        std::unordered_map<Entity, std::vector<bool>> m_entityBitsets;

        Entity m_nextEntity = 1;
    };
}  // namespace Dawn