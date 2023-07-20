//
// Created by 赵润朔 on 2023/7/16.
//

#ifndef RASEL_APPLICATION_H
#define RASEL_APPLICATION_H

#include <memory>
namespace Rasel {
    class Application {
    public:
        Application();
        virtual ~Application();
        static void Run();
    };    
    
    // To be defined in CLIENT
    std::unique_ptr<Application> CreateApplication();
}




#endif //RASEL_APPLICATION_H
