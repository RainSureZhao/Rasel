//
// Created by 赵润朔 on 2023/7/25.
//

#ifndef RASEL_IMGUILAYER_H
#define RASEL_IMGUILAYER_H

#include "Layer.h"

#include "ApplicationEvent.h"
#include "MouseEvent.h"
#include "KeyEvent.h"

namespace Rasel {

    class ImGuiLayer : public Layer{
    public:
        ImGuiLayer();
        ~ImGuiLayer() = default;
        
        void OnAttach() override;
        void OnDetach() override;
        void OnImGuiRender() override;
        
        void Begin();
        void End();
        
    private:
        float m_Time = 0.0f;
    };

} // Rasel

#endif //RASEL_IMGUILAYER_H
