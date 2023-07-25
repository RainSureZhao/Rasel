//
// Created by 赵润朔 on 2023/7/16.
//
#include "Rasel.h"

class ExampleLayer : public Rasel::Layer {
public:
    ExampleLayer() : Layer("Example") {}
    void OnUpdate() override {
        RZ_Client_INFO("ExampleLayer::Update");
    }
    void OnEvent(Rasel::Event& event) override {
        RZ_Client_TRACE("{0}", event);
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