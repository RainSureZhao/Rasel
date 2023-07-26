//
// Created by 赵润朔 on 2023/7/25.
//

#ifndef RASEL_IMGUILAYER_H
#define RASEL_IMGUILAYER_H

#include "Layer.h"
#include "Application.h"
#include "MouseEvent.h"
#include "KeyEvent.h"

namespace Rasel {

    class ImGuiLayer : public Layer{
    public:
        ImGuiLayer();
        ~ImGuiLayer() override = default;
        
        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event& event) override;
        
    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);
        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnKeyTypedEvent(KeyTypedEvent& e);
        bool OnWindowResizeEvent(WindowResizeEvent& e);
    private:
        float m_Time = 0.0f;
    };

} // Rasel

#endif //RASEL_IMGUILAYER_H
