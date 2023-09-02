//
// Created by 赵润朔 on 2023/9/1.
//

#ifndef RASEL_SANDBOX2D_H
#define RASEL_SANDBOX2D_H

#include "Rasel.h"

class SandBox2D : public Rasel::Layer{
public:
    SandBox2D();
    virtual ~SandBox2D() = default;
    
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    
    void OnUpdate(Rasel::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(Rasel::Event& e) override;
    
private:
    Rasel::OrthographicCameraController m_CameraController;
    
    // Temp
    Rasel::Ref<Rasel::VertexArray> m_SquareVA;
    Rasel::Ref<Rasel::Shader> m_FlatColorShader;
    
    Rasel::Ref<Rasel::Texture2D> m_CheckerboardTexture;
    glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};
};


#endif //RASEL_SANDBOX2D_H
