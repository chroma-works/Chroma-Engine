#pragma once

#include <sstream>
#include "Event.h"


//from: https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Events/KeyEvent.h
namespace Chroma
{
    class KeyEvent : public Event
    {
    public:
        inline int GetKeyCode() { return m_key_code; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        KeyEvent(int key_code)
            :m_key_code(key_code)
        {}
        int m_key_code;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int key_code, int repeat)
            : KeyEvent(key_code), m_repeat_count(repeat)
        {}

        inline int GetRepeatCount() { return m_repeat_count; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_key_code << " (" << m_repeat_count << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        int m_repeat_count;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int key_code)
            :KeyEvent(key_code)
        {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_key_code;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };


    class KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(int key_code)
            : KeyEvent(key_code) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_key_code;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };
}