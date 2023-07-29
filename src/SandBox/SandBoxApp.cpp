//
// Created by 赵润朔 on 2023/7/16.
//
#include "Rasel.h"
#include "imgui.h"

class ExampleLayer : public Rasel::Layer {
public:
    ExampleLayer() : Layer("Example") {}
    void OnUpdate() override {
        RZ_Client_INFO("ExampleLayer::Update");
        if(Rasel::Input::IsKeyPressed(RZ_KEY_TAB))
            RZ_Client_TRACE("Tab key is pressed (poll)");
    }
    void OnEvent(Rasel::Event& event) override {
        RZ_Client_TRACE("{0}", event);
        if(event.GetEventType() == Rasel::EventType::KeyPressed) {
            auto& e = dynamic_cast<Rasel::KeyPressedEvent&>(event);
            if(e.GetKeyCode() == RZ_KEY_TAB) {
                RZ_CORE_TRACE("Tab key is pressed (event)");
            }
            RZ_CORE_TRACE("{0}", (char)e.GetKeyCode());
        }
    }

    void OnImGuiRender() override {
        ImGui::Begin("Test");
        ImGui::Text("Hello World");
        ImGui::End();
    }

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