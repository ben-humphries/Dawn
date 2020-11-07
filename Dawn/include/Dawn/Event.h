#pragma once

#include <functional>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "Dawn/KeyCode.h"
#include "Dawn/MouseCode.h"

namespace Dawn
{
//Member functions need to be bound to an object before being submitted to the EventHandler.
#define BIND_EVENT_MEMBER_FN(func) std::bind(&func, this, std::placeholders::_1)

    enum EventType {
        WindowClosed,
        WindowResized,
        WindowMoved,

        KeyPressed,
        KeyReleased,

        MouseMoved,
        MousePressed,
        MouseReleased,
        MouseScrolled
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

    ////
    ////
    //// EVENT DEFINITIONS
    ////
    ////

    //// WINDOW

    class WindowClosedEvent : public Event
    {
       public:
        WindowClosedEvent()
        {
        }

        EVENT_NO_PARAM_GET_STRING(WindowClosedEvent)
        EVENT_GET_TYPE(WindowClosed)
    };

    class WindowResizedEvent : public Event
    {
       public:
        WindowResizedEvent(int width, int height)
            : m_width(width), m_height(height)
        {
        }

        int getWidth() const
        {
            return m_width;
        }

        int getHeight() const
        {
            return m_height;
        }

        std::string toString() const override
        {
            std::stringstream s;
            s << "WindowResizedEvent [width: " << m_width << " height: " << m_height << "]";
            return s.str();
        }

        EVENT_GET_TYPE(WindowResized)

       private:
        int m_width, m_height;
    };

    class WindowMovedEvent : public Event
    {
       public:
        WindowMovedEvent(int x, int y)
            : m_x(x), m_y(y)
        {
        }

        int getX() const
        {
            return m_x;
        }
        int getY() const
        {
            return m_y;
        }

        std::string toString() const override
        {
            std::stringstream s;
            s << "WindowMovedEvent [x: " << m_x << " y: " << m_y << "]";
            return s.str();
        }

        EVENT_GET_TYPE(WindowMoved)

       private:
        int m_x, m_y;
    };

    //// KEYBOARD

    class KeyPressedEvent : public Event
    {
       public:
        KeyPressedEvent(KeyCode keyCode)
            : m_keyCode(keyCode)
        {
        }

        KeyCode getKeyCode() const
        {
            return m_keyCode;
        }

        std::string toString() const override
        {
            std::stringstream s;
            s << "KeyPressedEvent [KeyCode: " << static_cast<int32_t>(m_keyCode) << "]";
            return s.str();
        }

        EVENT_GET_TYPE(KeyPressed)

       private:
        KeyCode m_keyCode;
    };

    class KeyReleasedEvent : public Event
    {
       public:
        KeyReleasedEvent(KeyCode keyCode)
            : m_keyCode(keyCode)
        {
        }

        KeyCode getKeyCode() const
        {
            return m_keyCode;
        }

        std::string toString() const override
        {
            std::stringstream s;
            s << "KeyReleasedEvent [KeyCode: " << static_cast<int32_t>(m_keyCode) << "]";
            return s.str();
        }

        EVENT_GET_TYPE(KeyReleased)

       private:
        KeyCode m_keyCode;
    };

    //// MOUSE

    class MouseMovedEvent : public Event
    {
       public:
        MouseMovedEvent(float x, float y)
            : m_x(x), m_y(y)
        {
        }

        float getX() const
        {
            return m_x;
        }
        float getY() const
        {
            return m_y;
        }

        std::string toString() const override
        {
            std::stringstream s;
            s << "MouseMovedEvent [x: " << m_x << " y: " << m_y << "]";
            return s.str();
        }

        EVENT_GET_TYPE(MouseMoved)

       private:
        float m_x, m_y;
    };

    class MousePressedEvent : public Event
    {
       public:
        MousePressedEvent(MouseCode mouseCode)
            : m_mouseCode(mouseCode)
        {
        }

        MouseCode getMouseCode() const
        {
            return m_mouseCode;
        }

        std::string toString() const override
        {
            std::stringstream s;
            s << "MousePressedEvent [MouseCode: " << static_cast<int32_t>(m_mouseCode) << "]";
            return s.str();
        }

        EVENT_GET_TYPE(MousePressed)

       private:
        MouseCode m_mouseCode;
    };

    class MouseReleasedEvent : public Event
    {
       public:
        MouseReleasedEvent(MouseCode mouseCode)
            : m_mouseCode(mouseCode)
        {
        }

        MouseCode getMouseCode() const
        {
            return m_mouseCode;
        }

        std::string toString() const override
        {
            std::stringstream s;
            s << "MouseReleasedEvent [MouseCode: " << static_cast<int32_t>(m_mouseCode) << "]";
            return s.str();
        }

        EVENT_GET_TYPE(MouseReleased)

       private:
        MouseCode m_mouseCode;
    };

    class MouseScrolledEvent : public Event
    {
       public:
        MouseScrolledEvent(float x, float y)
            : m_x(x), m_y(y)
        {
        }

        float getX() const
        {
            return m_x;
        }

        float getY() const
        {
            return m_y;
        }

        std::string toString() const override
        {
            std::stringstream s;
            s << "MouseScrolledEvent [x: " << m_x << " y: " << m_y << "]";
            return s.str();
        }

        EVENT_GET_TYPE(MouseScrolled)

       private:
        float m_x, m_y;
    };
}  // namespace Dawn