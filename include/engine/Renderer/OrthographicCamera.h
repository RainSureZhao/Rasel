//
// Created by 赵润朔 on 2023/8/4.
//

#ifndef RASEL_ORTHOGRAPHICCAMERA_H
#define RASEL_ORTHOGRAPHICCAMERA_H

#include "glm/glm.hpp"

namespace Rasel {

    class OrthographicCamera {
    public:
        OrthographicCamera() = default;
        OrthographicCamera(float left, float right, float bottom, float top);
        
        void SetProjection(float left, float right, float bottom, float top);
        
        [[nodiscard]] const glm::vec3& GetPosition() const {return m_Position;}
        void SetPosition(const glm::vec3& position) {
            m_Position = position;
            RecalculateViewMatrix();
        }
        
        [[nodiscard]] float GetRotation() const {return m_Rotation;}
        void SetRotation(float rotation) {
            m_Rotation = rotation;
            RecalculateViewMatrix();
        }
        
        [[nodiscard]] const glm::mat4& GetProjectionMatrix() const {return m_ProjectionMatrix;}
        [[nodiscard]] const glm::mat4& GetViewMatrix() const {return m_ViewMatrix;}
        [[nodiscard]] const glm::mat4& GetViewProjectionMatrix() const {return m_ViewProjectionMatrix;}
        
    private:
        void RecalculateViewMatrix();
        
    private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;
        
        glm::vec3 m_Position = glm::vec3(0.0f);
        float m_Rotation = 0.0f;
    };

} // Rasel

#endif //RASEL_ORTHOGRAPHICCAMERA_H
