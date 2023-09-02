//
// Created by 赵润朔 on 2023/7/16.
//

#ifndef RASEL_ENTRYPOINT_H
#define RASEL_ENTRYPOINT_H

#include "Log.h"
#include "stdafx.h"

extern std::unique_ptr<Rasel::Application> Rasel::CreateApplication();

int main(int argc, char** argv)
{
    Rasel::Log::Init();
    RZ_CORE_WARN("Initialized Log!");
    auto App = Rasel::CreateApplication();
    App->Run();
    return 0;
}

#endif //RASEL_ENTRYPOINT_H
