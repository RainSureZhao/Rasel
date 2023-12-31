//
// Created by 赵润朔 on 2023/7/21.
//

#ifndef RASEL_MOUSEEVENT_H
#define RASEL_MOUSEEVENT_H

#include "Event.h"
#include "stdafx.h"
#include "KeyCodes.h"
#include "MouseCodes.h"

namespace Rasel {
    class MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}
        [[nodiscard]] float GetX() const  {return m_MouseX;}
        [[nodiscard]] float GetY() const {return m_MouseY;}
        
        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseMoveEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved);
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
        
    private:
        float m_MouseX, m_MouseY;
    };
    
    class MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}
        [[nodiscard]] float GetXOffset() const {return m_XOffset;}
        [[nodiscard]] float GetYOffset() const {return m_YOffset;}
        
        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
            return ss.str();
        }
        EVENT_CLASS_TYPE(MouseScrolled);

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
    private:
        float m_XOffset, m_YOffset;
    };
    
    class MouseButtonEvent : public Event {
    public:
        [[nodiscard]] MouseCode GetMouseButton() const {return m_Button;}
        
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
    protected:
        explicit MouseButtonEvent(MouseCode button) : m_Button(button) {}
        MouseCode m_Button;
    };
    
    class MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        explicit MouseButtonPressedEvent(MouseCode button) : MouseButtonEvent(button) {}
        
        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }
        EVENT_CLASS_TYPE(MouseButtonPressed);
    };
    
    class MouseButtonReleasedEvent : public MouseButtonEvent {
    public:
        explicit MouseButtonReleasedEvent(MouseCode Button) : MouseButtonEvent(Button) {}
    
        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        }
        
        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}
#endif //RASEL_MOUSEEVENT_H
