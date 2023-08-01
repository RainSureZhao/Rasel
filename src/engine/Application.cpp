//
// Created by 赵润朔 on 2023/7/16.
//
        
#include "Application.h"
#include "Log.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Rasel{
    std::shared_ptr<Application> Application::s_Instance = nullptr;
    Application::Application()
    {
        RZ_CORE_ASSERT(!s_Instance, "Application already exists!");
        std::filesystem::current_path(R"(E:\Code\Cpp_project\Rasel)");
        s_Instance = std::shared_ptr<Application>(this);
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback([this](auto && PH1) { Application::OnEvent(std::forward<decltype(PH1)>(PH1)); });
        
         m_ImGuiLayer = std::make_unique<ImGuiLayer>();
         PushOverlay(std::move(m_ImGuiLayer));
         
         glGenVertexArrays(1, &m_VertexArray);
         glBindVertexArray(m_VertexArray);
         
         
         std::vector<float> vertices {
             -0.5f, -0.5f, 0.0f,
              0.5f, -0.5f, 0.0f,
              0.0f,  0.5f, 0.0f
         };
         
         m_VertexBuffer = std::unique_ptr<VertexBuffer>(VertexBuffer::Create(vertices.data(), sizeof(float) * vertices.size()));
         
         glBufferData(GL_ARRAY_BUFFER, sizeof (float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
         
         glEnableVertexAttribArray(0);
         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
         
         std::vector<unsigned int> indices {
             0, 1, 2
         };
         m_IndexBuffer = std::unique_ptr<IndexBuffer>(IndexBuffer::Create(indices.data(), indices.size()));
         
         
         
         
         std::ifstream vertexShaderFile(R"(shader\VertexShader.glsl)");
         std::ifstream fragmentShaderFile(R"(shader\FragmentShader.glsl)");
         
         std::string VertexShaderSource((std::istreambuf_iterator<char>(vertexShaderFile)), std::istreambuf_iterator<char>());
         std::string FragmentShaderSource((std::istreambuf_iterator<char>(fragmentShaderFile)), std::istreambuf_iterator<char>());
         
         
         m_Shader = std::make_unique<Shader>(VertexShaderSource, FragmentShaderSource);
    }
    
    Application::~Application() = default;
    
    void Application::Run() {
        while(m_Running) {
            glClearColor(0.2, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Shader->Bind();
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, static_cast<int>(m_IndexBuffer->GetCount()), GL_UNSIGNED_INT, nullptr);
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
        layer->OnAttach();
        m_LayerStack.PushLayer(std::move(layer));
    }

    void Application::PushOverlay(std::unique_ptr<Layer> overlay) {
        overlay->OnAttach();
        m_LayerStack.PushOverlay(std::move(overlay));
    }
}
