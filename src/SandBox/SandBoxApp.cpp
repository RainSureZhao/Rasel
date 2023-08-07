//
// Created by 赵润朔 on 2023/7/16.
//
#include "Rasel.h"
#include "imgui.h"

class ExampleLayer : public Rasel::Layer {
public:
    ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) {
        std::filesystem::current_path(R"(E:\Code\Cpp_project\Rasel)");
        m_VertexArray.reset(Rasel::VertexArray::Create());

        std::vector<float> vertices {
                -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
                0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
                0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };
        std::shared_ptr<Rasel::VertexBuffer> vertexBuffer;
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
        std::shared_ptr<Rasel::IndexBuffer> indexBuffer;
        indexBuffer.reset(Rasel::IndexBuffer::Create(indices.data(), indices.size()));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_Shader = std::make_unique<Rasel::Shader>(R"(shader\VertexShader.glsl)", R"(shader\FragmentShader.glsl)");

        m_SquareVA.reset(Rasel::VertexArray::Create());

        std::vector<float> squareVertices ({
           -0.75f, -0.75f, 0.0f,
           0.75f, -0.75f, 0.0f,
           0.75f, 0.75f, 0.0f,
           -0.75f, 0.75f, 0.0f
       });

        std::shared_ptr<Rasel::VertexBuffer> squareVB;
        squareVB.reset(Rasel::VertexBuffer::Create(squareVertices.data(), sizeof(float) * squareVertices.size()));
        squareVB->SetLayout({
            {"a_Position", Rasel::ShaderDataType::Float3}
        });
        m_SquareVA->AddVertexBuffer(squareVB);

        std::vector<uint32_t> squareIndices = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<Rasel::IndexBuffer> squareIB;
        squareIB.reset(Rasel::IndexBuffer::Create(squareIndices.data(), sizeof(float) * squareIndices.size()));
        m_SquareVA->SetIndexBuffer(squareIB);

        m_BlueShader.reset(new Rasel::Shader(R"(shader/BlueVertexShader.glsl)", R"(shader/BlueFragmentShader.glsl)"));
    }
    void OnUpdate(Rasel::Timestep timestep) override {
        if(Rasel::Input::IsKeyPressed(RZ_KEY_LEFT)) {
            m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
        } else if(Rasel::Input::IsKeyPressed(RZ_KEY_RIGHT)) {
            m_CameraPosition.x += m_CameraMoveSpeed * timestep;
        }
        
        if(Rasel::Input::IsKeyPressed(RZ_KEY_UP)) {
            m_CameraPosition.y += m_CameraMoveSpeed * timestep;
        } else if(Rasel::Input::IsKeyPressed(RZ_KEY_DOWN)) {
            m_CameraPosition.y -= m_CameraMoveSpeed * timestep;
        }
        
        if(Rasel::Input::IsKeyPressed(RZ_KEY_A)) {
            m_CameraRotation += m_CameraRotationSpeed * timestep;
        } else if(Rasel::Input::IsKeyPressed(RZ_KEY_D)) {
            m_CameraRotation -= m_CameraRotationSpeed * timestep;
        }
        
        Rasel::RendererCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Rasel::RendererCommand::Clear();
        
        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);
        
        Rasel::Renderer::BeginScene(m_Camera);
        
        Rasel::Renderer::Submit(m_BlueShader, m_SquareVA);
        Rasel::Renderer::Submit(m_Shader, m_VertexArray);
        
        Rasel::Renderer::EndScene();
        
    }
    void OnEvent(Rasel::Event& event) override {
        
    }

    void OnImGuiRender() override {
        
    }
private:
    std::shared_ptr<Rasel::VertexArray> m_VertexArray;
    std::shared_ptr<Rasel::Shader> m_Shader;

    std::shared_ptr<Rasel::Shader> m_BlueShader;
    std::shared_ptr<Rasel::VertexArray> m_SquareVA;

    Rasel::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 5.0f;
    
    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 180.0f;
};

class SandBox : public Rasel::Application{
public:
    SandBox() { 
        PushLayer(std::make_unique<ExampleLayer>());
    }
    ~SandBox() = default;
};

std::unique_ptr<Rasel::Application> Rasel::CreateApplication() {
    return std::make_unique<SandBox>();
}