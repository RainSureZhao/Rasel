//
// Created by 赵润朔 on 2023/7/16.
//
#include "Rasel.h"
#include "EntryPoint.h"
#include "Core.h"
#include "SandBox2D.h"


class SandBox : public Rasel::Application{
public:
    SandBox() { 
        // PushLayer(std::make_unique<ExampleLayer>());
        PushLayer(std::make_unique<SandBox2D>());
    }
    ~SandBox() = default;
};

Rasel::Scope<Rasel::Application> Rasel::CreateApplication() {
    return CreateScope<SandBox>();
}