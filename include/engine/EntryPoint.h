//
// Created by 赵润朔 on 2023/7/16.
//

#ifndef RASEL_ENTRYPOINT_H
#define RASEL_ENTRYPOINT_H
#include "Rasel.h"
#include <iostream>
extern std::unique_ptr<Rasel::Application> Rasel::CreateApplication();

int main(int argc, char** argv)
{
    std::unique_ptr<Rasel::Application> App = Rasel::CreateApplication();
    App->Run();
}

#endif //RASEL_ENTRYPOINT_H
