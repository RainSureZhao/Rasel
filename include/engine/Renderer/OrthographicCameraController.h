//
// Created by 赵润朔 on 2023/8/31.
//

#ifndef RASEL_ORTHOGRAPHICCAMERACONTROLLER_H
#define RASEL_ORTHOGRAPHICCAMERACONTROLLER_H

#include "OrthographicCamera.h"
#include "Timestep.h"
#include "ApplicationEvent.h"
#include "MouseEvent.h"

namespace Rasel {

    class OrthographicCameraController {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);
        
        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);
        
        [[nodiscard]] OrthographicCamera& GetCamera() { return m_Camera; }
        [[nodiscard]] const OrthographicCamera& GetCamera() const { return m_Camera; }
        
        [[nodiscard]] float GetZoomLevel() const { return m_ZoomLevel; }
        void SetZoomLevel(float level) { m_ZoomLevel = level; }
        
    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);
        
        
    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        OrthographicCamera m_Camera;
        
        bool m_Rotation;
        
        glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
        float m_CameraRotation = 0.0f;
        float m_CameraTranslationSpeed = 5.0f;
    };

} // Rasel

#endif //RASEL_ORTHOGRAPHICCAMERACONTROLLER_H
