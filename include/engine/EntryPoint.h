//
// Created by 赵润朔 on 2023/7/16.
//

#ifndef RASEL_ENTRYPOINT_H
#define RASEL_ENTRYPOINT_H

#include "Log.h"
#include "stdafx.h"

int main(int argc, char** argv)
{
    Rasel::Log::Init();
    RZ_CORE_WARN("Initialized Log!");
    RZ_Client_INFO("Hello1111");
    std::unique_ptr<Rasel::Application> App = Rasel::CreateApplication();
    App->Run();
}

#endif //RASEL_ENTRYPOINT_H
