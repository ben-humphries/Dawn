// #include "ECS.h"

// namespace Dawn
// {

//     // template <class T>
//     // void EntityRegistry::addComponent(Entity e)
//     // {
//     //     int index = T::s_id;

//     //     //if the size of m_componentLists can't accommodate this index, resize it.
//     //     if (index >= m_componentLists.size()) {
//     //         m_componentLists.resize(index + 1);
//     //     }

//     //     m_componentLists[index][e] = T();
//     // }

//     // template <class T>
//     // T& EntityRegistry::getComponent(Entity e)
//     // {
//     //     int index = T::s_id;
//     //     return (T)m_componentLists[index][e];
//     // }

//     Entity EntityRegistry::addEntity()
//     {
//         //TODO: m_componentLists is empty when adding our first entity because we haven't called addComponent yet

//         //This automatically resizes our arrays so we can always index to the entity in our lists of components
//         // for (std::vector<Component*> componentList : m_componentLists) {
//         //     componentList.push_back(nullptr);
//         // }

//         return m_nextEntity++;
//     }
// }