//
// Created by 赵润朔 on 2023/7/16.
//
        
#include "Application.h"
#include "Log.h"
#include "GLFW/glfw3.h"
#include "Renderer.h"
#include "RendererCommand.h"

namespace Rasel{
    std::shared_ptr<Application> Application::s_Instance = nullptr;
    
    
    Application::Application() : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
        RZ_CORE_ASSERT(!s_Instance, "Application already exists!");
        std::filesystem::current_path(R"(E:\Code\Cpp_project\Rasel)");
        s_Instance = std::shared_ptr<Application>(this);
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback([this](auto && PH1) { Application::OnEvent(std::forward<decltype(PH1)>(PH1)); });
        
         m_ImGuiLayer = std::make_unique<ImGuiLayer>();
         PushOverlay(std::move(m_ImGuiLayer));
         
         m_VertexArray.reset(VertexArray::Create());
         
         std::vector<float> vertices {
             -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
              0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
              0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
         };
         std::shared_ptr<VertexBuffer> vertexBuffer;
         vertexBuffer.reset(VertexBuffer::Create(vertices.data(), sizeof(float) * vertices.size()));
         BufferLayout layout ({
            {"a_Position", ShaderDataType::Float3},
            {"a_Color", ShaderDataType::Float4}
         });
         vertexBuffer->SetLayout(layout);
         m_VertexArray->AddVertexBuffer(vertexBuffer);   
         
         std::vector<unsigned int> indices {
             0, 1, 2
         };
         std::shared_ptr<IndexBuffer> indexBuffer;
         indexBuffer.reset(IndexBuffer::Create(indices.data(), indices.size()));
         m_VertexArray->SetIndexBuffer(indexBuffer);
         
         m_Shader = std::make_unique<Shader>(R"(shader\VertexShader.glsl)", R"(shader\FragmentShader.glsl)");
         
         m_SquareVA.reset(VertexArray::Create());
         
         std::vector<float> squareVertices ({
             -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f,
             0.75f, 0.75f, 0.0f,
             -0.75f, 0.75f, 0.0f
         });
         
         std::shared_ptr<VertexBuffer> squareVB;
         squareVB.reset(VertexBuffer::Create(squareVertices.data(), sizeof(float) * squareVertices.size()));
         squareVB->SetLayout({
             {"a_Position", ShaderDataType::Float3}
         });
         m_SquareVA->AddVertexBuffer(squareVB);
         
         std::vector<uint32_t> squareIndices = { 0, 1, 2, 2, 3, 0 };
         std::shared_ptr<IndexBuffer> squareIB;
         squareIB.reset(IndexBuffer::Create(squareIndices.data(), sizeof(float) * squareIndices.size()));
         m_SquareVA->SetIndexBuffer(squareIB);
         
         m_BlueShader.reset(new Shader(R"(shader/BlueVertexShader.glsl)", R"(shader/BlueFragmentShader.glsl)"));
    }
    
    void Application::Run() {
        while(m_Running) {
            RendererCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
            RendererCommand::Clear();
            
            m_Camera.SetPosition({0.5f, 0.5f, 0.0f});
            m_Camera.SetRotation(45.0f);
            Renderer::BeginScene(m_Camera);
            
            Renderer::Submit(m_BlueShader, m_SquareVA);
            
            Renderer::Submit(m_Shader, m_VertexArray);
            
            Renderer::EndScene();
            for(auto &layer : m_LayerStack)
                layer->OnUpdate();
             m_ImGuiLayer->Begin();
            for(auto &layer : m_LayerStack)
                layer->OnImGuiRender();
             m_ImGuiLayer->End();
            m_Window->OnUpdate();
        }
        exit(0);
    }

    void Application::OnEvent(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>([this](auto &&PH1){ return OnWindowClosed(std::forward<decltype(PH1)>(PH1));});
        for(auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
            (*--it)->OnEvent(e);
            if(e.Handled)
                break;
        }
        RZ_CORE_TRACE("{0}", e);
    }

    bool Application::OnWindowClosed(WindowCloseEvent &e) {
        m_Running = false;
        return true;
    }

    void Application::PushLayer(std::unique_ptr<Layer> layer) {
        m_LayerStack.PushLayer(std::move(layer));
    }

    void Application::PushOverlay(std::unique_ptr<Layer> overlay) {
        m_LayerStack.PushOverlay(std::move(overlay));
    }
}
