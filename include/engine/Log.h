//
// Created by 赵润朔 on 2023/7/16.
//

#ifndef RASEL_LOG_H
#define RASEL_LOG_H

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Rasel {
    class Log {
    public:
        static void Init(); 
        
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;    
    };    
}
// Core log macros
#define RZ_CORE_TRACE(...)    ::Rasel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RZ_CORE_INFO(...)     ::Rasel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RZ_CORE_WARN(...)     ::Rasel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RZ_CORE_ERROR(...)    ::Rasel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RZ_CORE_FATAL(...)    ::Rasel::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define RZ_CORE_ASSERT(x, ...) { if(!(x)) { RZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

// Client log macros
#define RZ_Client_TRACE(...)    ::Rasel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RZ_Client_INFO(...)     ::Rasel::Log::GetClientLogger()->info(__VA_ARGS__)
#define RZ_Client_WARN(...)     ::Rasel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RZ_Client_ERROR(...)    ::Rasel::Log::GetClientLogger()->error(__VA_ARGS__)
#define RZ_Client_FATAL(...)    ::Rasel::Log::GetClientLogger()->fatal(__VA_ARGS__)
#endif //RASEL_LOG_H
