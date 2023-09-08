//
// Created by 赵润朔 on 2023/7/21.
//

#ifndef RASEL_KEYEVENT_H
#define RASEL_KEYEVENT_H


#include "Event.h"
#include "stdafx.h"

namespace Rasel {
    
    class KeyEvent : public Event {
    public:
        [[nodiscard]] KeyCode GetKeyCode() const {return m_KeyCode;}
        
        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
        
    protected:
        explicit KeyEvent(KeyCode keycode) : m_KeyCode(keycode) {}
        
        KeyCode m_KeyCode;
    };
    
    class KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(KeyCode keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}
        [[nodiscard]] int GetRepeatCount() const  { return m_RepeatCount;}
        
        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
            return ss.str();
        }
        EVENT_CLASS_TYPE(KeyPressed);
    private:
        int m_RepeatCount;
    };
    
    class KeyReleasedEvent: public KeyEvent {
    public:
        explicit KeyReleasedEvent(KeyCode keycode) : KeyEvent(keycode) {}
        
        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased);
    };
    
    class KeyTypedEvent: public KeyEvent {
    public:
        explicit KeyTypedEvent(KeyCode keycode) : KeyEvent(keycode) {}
        
        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped);
    };
}

#endif //RASEL_KEYEVENT_H
