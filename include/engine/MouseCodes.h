//
// Created by 赵润朔 on 2023/7/28.
//

#ifndef RASEL_MOUSECODES_H
#define RASEL_MOUSECODES_H

namespace Rasel{

    typedef enum class MouseCode : uint16_t
    {
        // From glfw3.h
        Button0                = 0,
        Button1                = 1,
        Button2                = 2,
        Button3                = 3,
        Button4                = 4,
        Button5                = 5,
        Button6                = 6,
        Button7                = 7,

        ButtonLast             = Button7,
        ButtonLeft             = Button0,
        ButtonRight            = Button1,
        ButtonMiddle           = Button2
    } Mouse;

    inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
    {
        os << static_cast<int32_t>(mouseCode);
        return os;
    }
}

#define RZ_MOUSE_BUTTON_0      ::Rasel::Mouse::Button0
#define RZ_MOUSE_BUTTON_1      ::Rasel::Mouse::Button1
#define RZ_MOUSE_BUTTON_2      ::Rasel::Mouse::Button2
#define RZ_MOUSE_BUTTON_3      ::Rasel::Mouse::Button3
#define RZ_MOUSE_BUTTON_4      ::Rasel::Mouse::Button4
#define RZ_MOUSE_BUTTON_5      ::Rasel::Mouse::Button5
#define RZ_MOUSE_BUTTON_6      ::Rasel::Mouse::Button6
#define RZ_MOUSE_BUTTON_7      ::Rasel::Mouse::Button7
#define RZ_MOUSE_BUTTON_LAST   ::Rasel::Mouse::ButtonLast
#define RZ_MOUSE_BUTTON_LEFT   ::Rasel::Mouse::ButtonLeft
#define RZ_MOUSE_BUTTON_RIGHT  ::Rasel::Mouse::ButtonRight
#define RZ_MOUSE_BUTTON_MIDDLE ::Rasel::Mouse::ButtonMiddle



#endif //RASEL_MOUSECODES_H
