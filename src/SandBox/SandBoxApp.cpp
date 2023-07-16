//
// Created by 赵润朔 on 2023/7/16.
//
#include "Rasel.h"

class SandBox : public Rasel::Application{
public:
    SandBox() = default;
    ~SandBox() = default;
};

std::unique_ptr<Rasel::Application> Rasel::CreateApplication() {
    std::cout << "Test1" << std::endl;
    return std::make_unique<Rasel::Application>();
}