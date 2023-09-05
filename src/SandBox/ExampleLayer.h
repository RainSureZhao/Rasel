//
// Created by 赵润朔 on 2023/9/5.
//

#ifndef RASEL_EXAMPLELAYER_H
#define RASEL_EXAMPLELAYER_H

#include "Rasel.h"

class ExampleLayer : public Rasel::Layer{
public:
    ExampleLayer();
    virtual ~ExampleLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    void OnEvent(Rasel::Event& e) override;
    void OnUpdate(Rasel::Timestep ts) override;
    virtual void OnImGuiRender() override;
private:
    Rasel::ShaderLibrary m_ShaderLibrary;
    Rasel::Ref<Rasel::VertexArray> m_VertexArray;
    Rasel::Ref<Rasel::Shader> m_Shader;

    Rasel::Ref<Rasel::Shader> m_BlueShader;
    Rasel::Ref<Rasel::VertexArray> m_SquareVA;

    Rasel::Ref<Rasel::Texture2D> m_Texture, m_LogoTexture;

    Rasel::OrthographicCameraController m_CameraController;

    glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
};


#endif //RASEL_EXAMPLELAYER_H
