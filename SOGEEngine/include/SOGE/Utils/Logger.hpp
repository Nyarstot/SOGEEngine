#ifndef SOGE_LOGGER_HPP
#define SOGE_LOGGER_HPP

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

// TODO: Remove memory include
#include <memory>

namespace soge
{
    class Logger
    {
    private:
        static std::shared_ptr<spdlog::logger> mEngineSideLogger;
        static std::shared_ptr<spdlog::logger> mApplicationSideLogger;

    public:
        static void Init();

        static std::shared_ptr<spdlog::logger>& GetEngineSideLogger() { return mEngineSideLogger; }
        static std::shared_ptr<spdlog::logger>& GetApplicationSideLogger() { return mApplicationSideLogger; }

    };
}

#define SOGE_TRACE_LOG(...)      ::soge::Logger::GetEngineSideLogger()->trace(__VA_ARGS__)
#define SOGE_INFO_LOG(...)       ::soge::Logger::GetEngineSideLogger()->info(__VA_ARGS__)
#define SOGE_WARN_LOG(...)       ::soge::Logger::GetEngineSideLogger()->warn(__VA_ARGS__)
#define SOGE_ERROR_LOG(...)      ::soge::Logger::GetEngineSideLogger()->error(__VA_ARGS__)

#define SOGE_APP_TRACE_LOG(...)  ::soge::Logger::GetApplicationSideLogger()->trace(__VA_ARGS__)
#define SOGE_APP_INFO_LOG(...)   ::soge::Logger::GetApplicationSideLogger()->info(__VA_ARGS__)
#define SOGE_APP_WARN_LOG(...)   ::soge::Logger::GetApplicationSideLogger()->warn(__VA_ARGS__)
#define SOGE_APP_ERROR_LOG(...)  ::soge::Logger::GetApplicationSideLogger()->error(__VA_ARGS__)

#endif // !SOGE_LOGGER_HPP
