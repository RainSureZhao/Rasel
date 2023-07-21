//
// Created by 赵润朔 on 2023/7/21.
//

#ifndef RASEL_KEYEVENT_H
#define RASEL_KEYEVENT_H

#include <sstream>
#include "Event.h"

namespace Rasel {
    
    class KeyEvent : public Event {
    public:
        [[nodiscard]] inline int GetKeyCode() const {return m_KeyCode;}
        
        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
        
    protected:
        explicit KeyEvent(int keycode) : m_KeyCode(keycode) {}
        
        int m_KeyCode;
    };
    
    class KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}
        [[nodiscard]] inline int GetRepeatCount() const  { return m_RepeatCount;}
        
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
        explicit KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}
        
        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased);
    };
}

#endif //RASEL_KEYEVENT_H
