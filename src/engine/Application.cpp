//
// Created by 赵润朔 on 2023/7/16.
//
        
#include "Application.h"
#include "Log.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Rasel{
    std::shared_ptr<Application> Application::s_Instance = nullptr;
    
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch(type) {
            case ShaderDataType::Float:    return GL_FLOAT;
            case ShaderDataType::Float2:   return GL_FLOAT;
            case ShaderDataType::Float3:   return GL_FLOAT;
            case ShaderDataType::Float4:   return GL_FLOAT;
            case ShaderDataType::Mat3:     return GL_FLOAT;
            case ShaderDataType::Mat4:     return GL_FLOAT;
            case ShaderDataType::Int:      return GL_INT;
            case ShaderDataType::Int2:     return GL_INT;
            case ShaderDataType::Int3:     return GL_INT;
            case ShaderDataType::Int4:     return GL_INT;
            case ShaderDataType::Bool:     return GL_BOOL;
        }
        
        RZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }
    
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
             -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
              0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
              0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
         };
         
         m_VertexBuffer = std::unique_ptr<VertexBuffer>(VertexBuffer::Create(vertices.data(), sizeof(float) * vertices.size()));
        {
            BufferLayout layout ({
                {"a_Position", ShaderDataType::Float3},
                {"a_Color", ShaderDataType::Float4}
            });
            m_VertexBuffer->SetLayout(layout);
        }

        uint32_t index = 0;
        const auto& layout = m_VertexBuffer->GetLayout();
        for(const auto& element : layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, static_cast<GLint>(element.GetComponentCount()), ShaderDataTypeToOpenGLBaseType(element.Type), 
                                  element.Normalized ? GL_TRUE : GL_FALSE, static_cast<GLint>(layout.GetStride()), reinterpret_cast<const void*>(element.Offset));
            index ++;
        }
         
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
