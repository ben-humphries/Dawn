#include "Dawn/Event.h"

#include <iterator>

namespace Dawn
{
    std::unordered_map<EventType,
                       std::vector<std::function<void(const Event& e)>>>
        EventHandler::m_eventMap;

    void EventHandler::Listen(EventType type,
                              std::function<void(const Event& e)> func)
    {
        m_eventMap.emplace(type,
                           std::vector<std::function<void(const Event& e)>>());

        auto result = m_eventMap.find(type);
        result->second.insert(result->second.end(), func);
    }

    void EventHandler::Submit(const Event& e)
    {
        auto result = m_eventMap.find(e.getType());
        if (result != m_eventMap.end()) {
            for (auto eventFunc : result->second) {
                eventFunc(e);
            }
        }
    }
}  // namespace Dawn