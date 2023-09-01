//
// Created by 赵润朔 on 2023/7/16.
//
#include "Rasel.h"
#include "glm/ext/matrix_transform.hpp"
#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"
#include "OpenGLShader.h"
#include "Core.h"
#include "SandBox2D.h"

class ExampleLayer : public Rasel::Layer {
public:
    ExampleLayer() : Layer("Example"), m_CameraController(1280.0f / 720.0f, true){
        std::filesystem::current_path(R"(E:\Code\Cpp_project\Rasel)");
        m_VertexArray = Rasel::VertexArray::Create();

        std::vector<float> vertices {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };
        Rasel::Ref<Rasel::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Rasel::VertexBuffer::Create(vertices.data(), sizeof(float) * vertices.size()));
        Rasel::BufferLayout layout ({
             {"a_Position", Rasel::ShaderDataType::Float3},
             {"a_Color", Rasel::ShaderDataType::Float4}
         });
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        std::vector<unsigned int> indices {
            0, 1, 2
        };
        Rasel::Ref<Rasel::IndexBuffer> indexBuffer;
        indexBuffer.reset(Rasel::IndexBuffer::Create(indices.data(), indices.size()));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_Shader = Rasel::Shader::Create("m_Shader", R"(shader\VertexShader.glsl)", R"(shader\FragmentShader.glsl)");

        m_SquareVA = Rasel::VertexArray::Create();

        std::vector<float> squareVertices ({
           -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
           0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
           0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
           -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
       });

        Rasel::Ref<Rasel::VertexBuffer> squareVB;
        squareVB.reset(Rasel::VertexBuffer::Create(squareVertices.data(), sizeof(float) * squareVertices.size()));
        squareVB->SetLayout({
            {"a_Position", Rasel::ShaderDataType::Float3},
            {"a_TexCoord", Rasel::ShaderDataType::Float2}
        });
        m_SquareVA->AddVertexBuffer(squareVB);

        std::vector<uint32_t> squareIndices = { 0, 1, 2, 2, 3, 0 };
        Rasel::Ref<Rasel::IndexBuffer> squareIB;
        squareIB.reset(Rasel::IndexBuffer::Create(squareIndices.data(), sizeof(float) * squareIndices.size()));
        m_SquareVA->SetIndexBuffer(squareIB);

        m_BlueShader = Rasel::Shader::Create("BlueShader", R"(shader/BlueVertexShader.glsl)", R"(shader/BlueFragmentShader.glsl)");

        // m_TextureShader.reset(Rasel::Shader::Create(R"(shader/TextureVertexShader.glsl)", R"(shader/TextureFragmentShader.glsl)"));
        // m_TextureShader = Rasel::Shader::Create(R"(shader/Texture.glsl)");
        auto textureShader = m_ShaderLibrary.Load(R"(shader/Texture.glsl)");
        m_Texture = Rasel::Texture2D::Create(R"(assets/textures/Checkerboard.png)");
        m_LogoTexture = Rasel::Texture2D::Create(R"(assets/textures/ChernoLogo.png)");
        
        std::dynamic_pointer_cast<Rasel::OpenGLShader>(textureShader)->Bind();
        std::dynamic_pointer_cast<Rasel::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
    }
    void OnUpdate(Rasel::Timestep timestep) override {
        m_CameraController.OnUpdate(timestep);
        
        Rasel::RendererCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Rasel::RendererCommand::Clear();
        
        Rasel::Renderer::BeginScene(m_CameraController.GetCamera());
        
        std::dynamic_pointer_cast<Rasel::OpenGLShader>(m_BlueShader)->Bind();
        std::dynamic_pointer_cast<Rasel::OpenGLShader>(m_BlueShader)->UploadUniformFloat3("u_Color", m_SquareColor);
        
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
        for(int x = 0; x < 20; x ++) {
            for(int y = 0; y < 20; y ++) {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Rasel::Renderer::Submit(m_BlueShader, m_SquareVA, transform);
            }
        }
        
      
        // Rasel::Renderer::Submit(m_Shader, m_VertexArray);
        auto textureShader = m_ShaderLibrary.Get("Texture");
        m_Texture->Bind();
        Rasel::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        
        m_LogoTexture->Bind();
        Rasel::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        Rasel::Renderer::EndScene();
        
    }
    void OnEvent(Rasel::Event& e) override {
        m_CameraController.OnEvent(e);
    }

    void OnImGuiRender() override {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }
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

class SandBox : public Rasel::Application{
public:
    SandBox() { 
        // PushLayer(std::make_unique<ExampleLayer>());
        PushLayer(std::make_unique<SandBox2D>());
    }
    ~SandBox() = default;
};

Rasel::Scope<Rasel::Application> Rasel::CreateApplication() {
    return std::make_unique<SandBox>();
}