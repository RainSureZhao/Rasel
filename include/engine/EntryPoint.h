//
// Created by 赵润朔 on 2023/7/16.
//

#ifndef RASEL_ENTRYPOINT_H
#define RASEL_ENTRYPOINT_H

#include "Log.h"
#include "stdafx.h"

int main(int argc, char** argv)
{
    RZ_PROFILE_BEGIN_SESSION("Initial Log", "RaselProfile-Log.json");
    Rasel::Log::Init();
    RZ_PROFILE_END_SESSION();
    
    
    RZ_PROFILE_BEGIN_SESSION("Startup", "RaselProfile-Startup.json");
    auto App = Rasel::CreateApplication();
    RZ_PROFILE_END_SESSION();
    
    RZ_PROFILE_BEGIN_SESSION("Runtime", "RaselProfile-Runtime.json");
    App->Run();
    RZ_PROFILE_END_SESSION();
    
    return 0;
}

#endif //RASEL_ENTRYPOINT_H
