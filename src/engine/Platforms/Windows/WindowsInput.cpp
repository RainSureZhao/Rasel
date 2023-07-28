//
// Created by 赵润朔 on 2023/7/27.
//

#include "WindowsInput.h"
#include "stdafx.h"
#include "GLFW/glfw3.h"
#include "Application.h"

namespace Rasel {
    bool WindowsInput::IsKeyPressedImpl(int keycode) {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(int button) {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::GetMousePositionImpl() {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return {static_cast<float>(xpos), static_cast<float>(ypos)};
    }

    float WindowsInput::GetMouseXImpl() {
        return GetMousePositionImpl().first;
    }

    float WindowsInput::GetMouseYImpl() {
        return GetMousePositionImpl().second;
    }
} // Rasel