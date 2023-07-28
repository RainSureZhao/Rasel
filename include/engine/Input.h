//
// Created by 赵润朔 on 2023/7/27.
//

#ifndef RASEL_INPUT_H
#define RASEL_INPUT_H

#include "stdafx.h"

namespace Rasel {
    class Input {
    public:
        inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode);}
        
        inline static bool IsMouseButtonPressed(int button) {return s_Instance->IsMouseButtonPressedImpl(button);}
        inline static std::pair<float, float> GetMousePosition() {return s_Instance->GetMousePositionImpl();}
        inline static float GetMouseX() {return s_Instance->GetMouseXImpl();}
        inline static float GetMouseY() {return s_Instance->GetMouseYImpl();}
        
    protected:
        
        virtual bool IsKeyPressedImpl(int keycode) = 0;
        virtual bool IsMouseButtonPressedImpl(int button) = 0;
        virtual std::pair<float, float> GetMousePositionImpl() = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;
        
    private:
        static Input* s_Instance;
    };
}

#endif //RASEL_INPUT_H
