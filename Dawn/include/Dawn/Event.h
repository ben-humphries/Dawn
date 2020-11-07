#pragma once

#include <functional>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace Dawn
{
//Member functions need to be bound to an object before being submitted to the EventHandler.
#define BIND_EVENT_MEMBER_FN(func) std::bind(&func, this, std::placeholders::_1)

    enum EventType {
        MouseMoved,
        MousePressed,
        MouseScrolled,
        WindowClosed,
        //...
    };

    class Event
    {
       public:
        virtual std::string toString() const = 0;
        virtual EventType getType() const = 0;
    };

    class EventHandler
    {
       public:
        //Note that Listen() will accept duplicates and will call a function however many times it has been submitted.
        static void Listen(EventType type, std::function<void(const Event& e)> func);
        static void Submit(const Event& e);

       private:
        static std::unordered_map<EventType, std::vector<std::function<void(const Event& e)>>> m_eventMap;
    };

#define EVENT_NO_PARAM_GET_STRING(eventClass) \
    \
std::string                                   \
    toString() const override                 \
    {                                         \
        std::stringstream s;                  \
        s << #eventClass << ": []";           \
        return s.str();                       \
    }

#define EVENT_GET_TYPE(eventType)      \
    EventType getType() const override \
    {                                  \
        return eventType;              \
    }

    class WindowClosedEvent : public Event
    {
       public:
        WindowClosedEvent()
        {
        }

        EVENT_NO_PARAM_GET_STRING(WindowClosedEvent)
        EVENT_GET_TYPE(WindowClosed)
    };

    class MouseMovedEvent : public Event
    {
       public:
        MouseMovedEvent(uint32_t x, uint32_t y)
            : m_x(x), m_y(y)
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

        std::string toString() const override
        {
            std::stringstream s;
            s << "MouseMovedEvent [x: " << m_x << " y: " << m_y << "]";
            return s.str();
        }

        EventType getType() const override
        {
            return MouseMoved;
        }

       private:
        uint32_t m_x, m_y;
    };
}  // namespace Dawn