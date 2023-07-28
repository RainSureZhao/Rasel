//
// Created by 赵润朔 on 2023/7/27.
//

#ifndef RASEL_WINDOWSINPUT_H
#define RASEL_WINDOWSINPUT_H

#include "Input.h"
namespace Rasel {

    class WindowsInput : public Input{
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;
        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };

} // Rasel

#endif //RASEL_WINDOWSINPUT_H
