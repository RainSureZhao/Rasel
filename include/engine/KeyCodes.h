//
// Created by 赵润朔 on 2023/7/28.
//

#ifndef RASEL_KEYCODES_H
#define RASEL_KEYCODES_H

namespace Rasel{
    typedef enum class KeyCode : uint16_t
    {
        // From glfw3.h
        Space               = 32,
        Apostrophe          = 39, /* ' */
        Comma               = 44, /* , */
        Minus               = 45, /* - */
        Period              = 46, /* . */
        Slash               = 47, /* / */

        D0                  = 48, /* 0 */
        D1                  = 49, /* 1 */
        D2                  = 50, /* 2 */
        D3                  = 51, /* 3 */
        D4                  = 52, /* 4 */
        D5                  = 53, /* 5 */
        D6                  = 54, /* 6 */
        D7                  = 55, /* 7 */
        D8                  = 56, /* 8 */
        D9                  = 57, /* 9 */

        Semicolon           = 59, /* ; */
        Equal               = 61, /* = */

        A                   = 65,
        B                   = 66,
        C                   = 67,
        D                   = 68,
        E                   = 69,
        F                   = 70,
        G                   = 71,
        H                   = 72,
        I                   = 73,
        J                   = 74,
        K                   = 75,
        L                   = 76,
        M                   = 77,
        N                   = 78,
        O                   = 79,
        P                   = 80,
        Q                   = 81,
        R                   = 82,
        S                   = 83,
        T                   = 84,
        U                   = 85,
        V                   = 86,
        W                   = 87,
        X                   = 88,
        Y                   = 89,
        Z                   = 90,

        LeftBracket         = 91,  /* [ */
        Backslash           = 92,  /* \ */
        RightBracket        = 93,  /* ] */
        GraveAccent         = 96,  /* ` */

        World1              = 161, /* non-US #1 */
        World2              = 162, /* non-US #2 */

        /* Function keys */
        Escape              = 256,
        Enter               = 257,
        Tab                 = 258,
        Backspace           = 259,
        Insert              = 260,
        Delete              = 261,
        Right               = 262,
        Left                = 263,
        Down                = 264,
        Up                  = 265,
        PageUp              = 266,
        PageDown            = 267,
        Home                = 268,
        End                 = 269,
        CapsLock            = 280,
        ScrollLock          = 281,
        NumLock             = 282,
        PrintScreen         = 283,
        Pause               = 284,
        F1                  = 290,
        F2                  = 291,
        F3                  = 292,
        F4                  = 293,
        F5                  = 294,
        F6                  = 295,
        F7                  = 296,
        F8                  = 297,
        F9                  = 298,
        F10                 = 299,
        F11                 = 300,
        F12                 = 301,
        F13                 = 302,
        F14                 = 303,
        F15                 = 304,
        F16                 = 305,
        F17                 = 306,
        F18                 = 307,
        F19                 = 308,
        F20                 = 309,
        F21                 = 310,
        F22                 = 311,
        F23                 = 312,
        F24                 = 313,
        F25                 = 314,

        /* Keypad */
        KP0                 = 320,
        KP1                 = 321,
        KP2                 = 322,
        KP3                 = 323,
        KP4                 = 324,
        KP5                 = 325,
        KP6                 = 326,
        KP7                 = 327,
        KP8                 = 328,
        KP9                 = 329,
        KPDecimal           = 330,
        KPDivide            = 331,
        KPMultiply          = 332,
        KPSubtract          = 333,
        KPAdd               = 334,
        KPEnter             = 335,
        KPEqual             = 336,

        LeftShift           = 340,
        LeftControl         = 341,
        LeftAlt             = 342,
        LeftSuper           = 343,
        RightShift          = 344,
        RightControl        = 345,
        RightAlt            = 346,
        RightSuper          = 347,
        Menu                = 348
    } Key;

    inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
    {
        os << static_cast<int32_t>(keyCode);
        return os;
    }
}

#define RZ_KEY_SPACE           ::Rasel::Key::Space
#define RZ_KEY_APOSTROPHE      ::Rasel::Key::Apostrophe    /* ' */
#define RZ_KEY_COMMA           ::Rasel::Key::Comma         /* , */
#define RZ_KEY_MINUS           ::Rasel::Key::Minus         /* - */
#define RZ_KEY_PERIOD          ::Rasel::Key::Period        /* . */
#define RZ_KEY_SLASH           ::Rasel::Key::Slash         /* / */
#define RZ_KEY_0               ::Rasel::Key::D0
#define RZ_KEY_1               ::Rasel::Key::D1
#define RZ_KEY_2               ::Rasel::Key::D2
#define RZ_KEY_3               ::Rasel::Key::D3
#define RZ_KEY_4               ::Rasel::Key::D4
#define RZ_KEY_5               ::Rasel::Key::D5
#define RZ_KEY_6               ::Rasel::Key::D6
#define RZ_KEY_7               ::Rasel::Key::D7
#define RZ_KEY_8               ::Rasel::Key::D8
#define RZ_KEY_9               ::Rasel::Key::D9
#define RZ_KEY_SEMICOLON       ::Rasel::Key::Semicolon     /* ; */
#define RZ_KEY_EQUAL           ::Rasel::Key::Equal         /* = */
#define RZ_KEY_A               ::Rasel::Key::A
#define RZ_KEY_B               ::Rasel::Key::B
#define RZ_KEY_C               ::Rasel::Key::C
#define RZ_KEY_D               ::Rasel::Key::D
#define RZ_KEY_E               ::Rasel::Key::E
#define RZ_KEY_F               ::Rasel::Key::F
#define RZ_KEY_G               ::Rasel::Key::G
#define RZ_KEY_H               ::Rasel::Key::H
#define RZ_KEY_I               ::Rasel::Key::I
#define RZ_KEY_J               ::Rasel::Key::J
#define RZ_KEY_K               ::Rasel::Key::K
#define RZ_KEY_L               ::Rasel::Key::L
#define RZ_KEY_M               ::Rasel::Key::M
#define RZ_KEY_N               ::Rasel::Key::N
#define RZ_KEY_O               ::Rasel::Key::O
#define RZ_KEY_P               ::Rasel::Key::P
#define RZ_KEY_Q               ::Rasel::Key::Q
#define RZ_KEY_R               ::Rasel::Key::R
#define RZ_KEY_S               ::Rasel::Key::S
#define RZ_KEY_T               ::Rasel::Key::T
#define RZ_KEY_U               ::Rasel::Key::U
#define RZ_KEY_V               ::Rasel::Key::V
#define RZ_KEY_W               ::Rasel::Key::W
#define RZ_KEY_X               ::Rasel::Key::X
#define RZ_KEY_Y               ::Rasel::Key::Y
#define RZ_KEY_Z               ::Rasel::Key::Z
#define RZ_KEY_LEFT_BRACKET    ::Rasel::Key::LeftBracket   /* [ */
#define RZ_KEY_BACKSLASH       ::Rasel::Key::Backslash     /* \ */
#define RZ_KEY_RIGHT_BRACKET   ::Rasel::Key::RightBracket  /* ] */
#define RZ_KEY_GRAVE_ACCENT    ::Rasel::Key::GraveAccent   /* ` */
#define RZ_KEY_WORLD_1         ::Rasel::Key::World1        /* non-US #1 */
#define RZ_KEY_WORLD_2         ::Rasel::Key::World2        /* non-US #2 */

#define RZ_KEY_ESCAPE          ::Rasel::Key::Escape
#define RZ_KEY_ENTER           ::Rasel::Key::Enter
#define RZ_KEY_TAB             ::Rasel::Key::Tab
#define RZ_KEY_BACKSPACE       ::Rasel::Key::Backspace
#define RZ_KEY_INSERT          ::Rasel::Key::Insert
#define RZ_KEY_DELETE          ::Rasel::Key::Delete
#define RZ_KEY_RIGHT           ::Rasel::Key::Right
#define RZ_KEY_LEFT            ::Rasel::Key::Left
#define RZ_KEY_DOWN            ::Rasel::Key::Down
#define RZ_KEY_UP              ::Rasel::Key::Up
#define RZ_KEY_PAGE_UP         ::Rasel::Key::PageUp
#define RZ_KEY_PAGE_DOWN       ::Rasel::Key::PageDown
#define RZ_KEY_HOME            ::Rasel::Key::Home
#define RZ_KEY_END             ::Rasel::Key::End
#define RZ_KEY_CAPS_LOCK       ::Rasel::Key::CapsLock
#define RZ_KEY_SCROLL_LOCK     ::Rasel::Key::ScrollLock
#define RZ_KEY_NUM_LOCK        ::Rasel::Key::NumLock
#define RZ_KEY_PRINT_SCREEN    ::Rasel::Key::PrintScreen
#define RZ_KEY_PAUSE           ::Rasel::Key::Pause
#define RZ_KEY_F1              ::Rasel::Key::F1
#define RZ_KEY_F2              ::Rasel::Key::F2
#define RZ_KEY_F3              ::Rasel::Key::F3
#define RZ_KEY_F4              ::Rasel::Key::F4
#define RZ_KEY_F5              ::Rasel::Key::F5
#define RZ_KEY_F6              ::Rasel::Key::F6
#define RZ_KEY_F7              ::Rasel::Key::F7
#define RZ_KEY_F8              ::Rasel::Key::F8
#define RZ_KEY_F9              ::Rasel::Key::F9
#define RZ_KEY_F10             ::Rasel::Key::F10
#define RZ_KEY_F11             ::Rasel::Key::F11
#define RZ_KEY_F12             ::Rasel::Key::F12
#define RZ_KEY_F13             ::Rasel::Key::F13
#define RZ_KEY_F14             ::Rasel::Key::F14
#define RZ_KEY_F15             ::Rasel::Key::F15
#define RZ_KEY_F16             ::Rasel::Key::F16
#define RZ_KEY_F17             ::Rasel::Key::F17
#define RZ_KEY_F18             ::Rasel::Key::F18
#define RZ_KEY_F19             ::Rasel::Key::F19
#define RZ_KEY_F20             ::Rasel::Key::F20
#define RZ_KEY_F21             ::Rasel::Key::F21
#define RZ_KEY_F22             ::Rasel::Key::F22
#define RZ_KEY_F23             ::Rasel::Key::F23
#define RZ_KEY_F24             ::Rasel::Key::F24
#define RZ_KEY_F25             ::Rasel::Key::F25

/* Keypad */
#define RZ_KEY_KP_0            ::Rasel::Key::KP0
#define RZ_KEY_KP_1            ::Rasel::Key::KP1
#define RZ_KEY_KP_2            ::Rasel::Key::KP2
#define RZ_KEY_KP_3            ::Rasel::Key::KP3
#define RZ_KEY_KP_4            ::Rasel::Key::KP4
#define RZ_KEY_KP_5            ::Rasel::Key::KP5
#define RZ_KEY_KP_6            ::Rasel::Key::KP6
#define RZ_KEY_KP_7            ::Rasel::Key::KP7
#define RZ_KEY_KP_8            ::Rasel::Key::KP8
#define RZ_KEY_KP_9            ::Rasel::Key::KP9
#define RZ_KEY_KP_DECIMAL      ::Rasel::Key::KPDecimal
#define RZ_KEY_KP_DIVIDE       ::Rasel::Key::KPDivide
#define RZ_KEY_KP_MULTIPLY     ::Rasel::Key::KPMultiply
#define RZ_KEY_KP_SUBTRACT     ::Rasel::Key::KPSubtract
#define RZ_KEY_KP_ADD          ::Rasel::Key::KPAdd
#define RZ_KEY_KP_ENTER        ::Rasel::Key::KPEnter
#define RZ_KEY_KP_EQUAL        ::Rasel::Key::KPEqual

#define RZ_KEY_LEFT_SHIFT      ::Rasel::Key::LeftShift
#define RZ_KEY_LEFT_CONTROL    ::Rasel::Key::LeftControl
#define RZ_KEY_LEFT_ALT        ::Rasel::Key::LeftAlt
#define RZ_KEY_LEFT_SUPER      ::Rasel::Key::LeftSuper
#define RZ_KEY_RIGHT_SHIFT     ::Rasel::Key::RightShift
#define RZ_KEY_RIGHT_CONTROL   ::Rasel::Key::RightControl
#define RZ_KEY_RIGHT_ALT       ::Rasel::Key::RightAlt
#define RZ_KEY_RIGHT_SUPER     ::Rasel::Key::RightSuper
#define RZ_KEY_MENU            ::Rasel::Key::Menu

#endif //RASEL_KEYCODES_H
