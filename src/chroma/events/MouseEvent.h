#pragma once

#include <chroma/events/Event.h>

namespace Chroma
{
    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y)
            :m_x(x), m_y(y)
        {}

        float inline GetX() { return m_x; }
        float inline GetY() { return m_y; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMoveEvent: " << m_x << ", " << m_y;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
        float m_x, m_y;
    };

    class MouseButtonEvent : public Event
    {
    public:
        MouseButtonEvent(int button)
            :m_button_code(button)
        {}

        inline int GetButton() { return m_button_code; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    protected:
        int m_button_code;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button)
            :MouseButtonEvent(button)
        {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_button_code;
            return ss.str();
        }
        EVENT_CLASS_TYPE(MouseButtonPressed)    
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button)
            :MouseButtonEvent(button)
        {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_button_code;
            return ss.str();
        }
        EVENT_CLASS_TYPE(MouseButtonReleased)
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float x, float y)
            :m_x(x), m_y(y)
        {}

        inline float GetX() const { return m_x; }
        inline float GetY() const { return m_y; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << GetX() << ", " << GetY();
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
        float m_x, m_y;
    };
}
