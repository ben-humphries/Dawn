#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

namespace Dawn
{
    enum EventType {
        MouseMoved,
        MousePressed,
        MouseScrolled,
        //...

        None  // Must be last for iteration to work in Listen()
    };

    class Event
    {
       public:
        virtual const std::string& toString() const = 0;
        virtual EventType getType() const = 0;
    };

    class EventHandler
    {
       public:
        static void Listen(EventType type,
                           std::function<void(const Event& e)> func);
        static void Submit(const Event& e);

       private:
        static std::unordered_map<
            EventType, std::vector<std::function<void(const Event& e)>>>
            m_eventMap;
    };

    class MouseMovedEvent : public Event
    {
       public:
        MouseMovedEvent(uint32_t x, uint32_t y) : m_x(x), m_y(y)
        {
        }

        uint32_t getX() const
        {
            return m_x;
        }
        uint32_t getY() const
        {
            return m_y;
        }

        const std::string& toString() const override
        {
            return "MouseMovedEvent: x y";
        }

        EventType getType() const override
        {
            return MouseMoved;
        }

       private:
        uint32_t m_x, m_y;
    };
}  // namespace Dawn