//
// Created by 赵润朔 on 2023/7/27.
//

#ifndef RASEL_INPUT_H
#define RASEL_INPUT_H

#include "stdafx.h"
#include "Core.h"
#include "KeyCodes.h"
#include "MouseCodes.h"

namespace Rasel {
    class Input {
    public:
        virtual ~Input() = default;
        
        inline static bool IsKeyPressed(KeyCode keycode) { return s_Instance->IsKeyPressedImpl(keycode);}
        
        inline static bool IsMouseButtonPressed(MouseCode button) {return s_Instance->IsMouseButtonPressedImpl(button);}
        inline static std::pair<float, float> GetMousePosition() {return s_Instance->GetMousePositionImpl();}
        inline static float GetMouseX() {return s_Instance->GetMouseXImpl();}
        inline static float GetMouseY() {return s_Instance->GetMouseYImpl();}

        static Scope<Input> Create();
    protected:
        
        virtual bool IsKeyPressedImpl(KeyCode keycode) = 0;
        virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;
        virtual std::pair<float, float> GetMousePositionImpl() = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;
        
    private:
        static Scope<Input> s_Instance;
    };
}

#endif //RASEL_INPUT_H
