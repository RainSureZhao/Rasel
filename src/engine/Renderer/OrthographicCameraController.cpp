//
// Created by 赵润朔 on 2023/8/31.
//

#include "stdafx.h"
#include "OrthographicCameraController.h"
#include "Input.h"
#include "KeyCodes.h"


namespace Rasel {
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) : m_AspectRatio(aspectRatio),
    m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
    {
    }

    void OrthographicCameraController::OnUpdate(Rasel::Timestep ts) {
        RZ_PROFILE_FUNCTION();
        if (Input::IsKeyPressed(RZ_KEY_A)) {
            m_CameraPosition.x -= std::cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
            m_CameraPosition.y -= std::sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;

        } else if(Input::IsKeyPressed(RZ_KEY_D)) {
            m_CameraPosition.x += std::cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
            m_CameraPosition.y += std::sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
        }
        
        if(Input::IsKeyPressed(RZ_KEY_W)) {
            m_CameraPosition.x += -std::sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
            m_CameraPosition.y += std::cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
        } else if(Input::IsKeyPressed(RZ_KEY_S)) {
            m_CameraPosition.x -= -std::sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
            m_CameraPosition.y -= std::cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
        }
        
        if(m_Rotation) {
            if(Input::IsKeyPressed(RZ_KEY_Q)) {
                m_CameraRotation -= m_CameraRotationSpeed * ts;
            } else if(Input::IsKeyPressed(RZ_KEY_E)) {
                m_CameraRotation += m_CameraRotationSpeed * ts;
            }
            m_Camera.SetRotation(m_CameraRotation);
        
            if(m_CameraRotation > 180.0f) m_CameraRotation -= 360.0f;
            else if(m_CameraRotation <= -180.0f) m_CameraRotation += 360.0f;
        }

        m_Camera.SetPosition(m_CameraPosition);
        m_CameraTranslationSpeed = m_ZoomLevel;
    }
    
    void OrthographicCameraController::OnEvent(Rasel::Event &e) {
        RZ_PROFILE_FUNCTION();
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>([this](auto &&PH1){ return OnMouseScrolled(std::forward<decltype(PH1)>(PH1));});
        dispatcher.Dispatch<WindowResizeEvent>([this](auto &&PH1){ return OnWindowResized(std::forward<decltype(PH1)>(PH1));});
    }

    bool OrthographicCameraController::OnMouseScrolled(Rasel::MouseScrolledEvent &e) {
        RZ_PROFILE_FUNCTION();
        m_ZoomLevel -= e.GetYOffset() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(Rasel::WindowResizeEvent &e) {
        RZ_PROFILE_FUNCTION();
        m_AspectRatio = static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight());
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
} // Rasel