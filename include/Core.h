//
// Created by 赵润朔 on 2023/8/17.
//

#ifndef RASEL_CORE_H
#define RASEL_CORE_H
#include <memory>

namespace Rasel {
    template<typename T>
    using Scope = std::unique_ptr<T>;
    
    template<typename T>
    using Ref = std::shared_ptr<T>;
};

#endif //RASEL_CORE_H
