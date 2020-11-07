#include "Dawn/Event.h"

#include <iterator>

namespace Dawn
{
    std::unordered_map<EventType, std::vector<std::function<void(const Event& e)>>> EventHandler::m_eventMap;

    void EventHandler::Listen(EventType type, std::function<void(const Event& e)> func)
    {
        //If there is no vector in the map for this event type, add it.
        m_eventMap.emplace(type, std::vector<std::function<void(const Event& e)>>());

        auto result = m_eventMap.find(type);
        std::vector<std::function<void(const Event& e)>> v = result->second;

        result->second.insert(result->second.end(), func);
    }

    void EventHandler::Submit(const Event& e)
    {
        //Call all functions listening for this event, if there are any.
        auto result = m_eventMap.find(e.getType());
        if (result != m_eventMap.end()) {
            for (auto eventFunc : result->second) {
                eventFunc(e);
            }
        }
    }
}  // namespace Dawn