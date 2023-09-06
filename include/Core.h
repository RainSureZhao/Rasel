//
// Created by 赵润朔 on 2023/8/17.
//

#ifndef RASEL_CORE_H
#define RASEL_CORE_H
#include <memory>

#define RZ_PLATFORM_WINDOWS 1
#define RZ_PLATFORM_WINDOWS 1

namespace Rasel {
    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    
    
    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
};

#endif //RASEL_CORE_H
