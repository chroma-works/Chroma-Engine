#pragma once
#include <spdlog/spdlog.h>

namespace Chroma {

    class Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_logger; }
    private:
        static std::shared_ptr<spdlog::logger> s_logger;
    };

}

#define CH_TRACE(...)    ::Chroma::Log::GetLogger()->trace(__VA_ARGS__)
#define CH_INFO(...)     ::Chroma::Log::GetLogger()->info(__VA_ARGS__)
#define CH_WARN(...)     ::Chroma::Log::GetLogger()->warn(__VA_ARGS__)
#define CH_ERROR(...)    ::Chroma::Log::GetLogger()->error(__VA_ARGS__)
#define CH_FATAL(...)    ::Chroma::Log::GetLogger()->fatal(__VA_ARGS__)
#define CH_ASSERT(x, ...) { if(!(x)) { CH_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }