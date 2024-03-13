#include "sogepch.hpp"

#include "SOGE/Utils/Logger.hpp"

namespace soge
{
    std::shared_ptr<spdlog::logger> Logger::mEngineSideLogger;
    std::shared_ptr<spdlog::logger> Logger::mApplicationSideLogger;

    void Logger::Init()
    {
        spdlog::set_pattern("%^[%T] [%n %l]: %v%$");

        mEngineSideLogger = std::shared_ptr<spdlog::logger>(spdlog::stdout_color_mt("ENGINE").get());
        mEngineSideLogger->set_level(spdlog::level::trace);

        mApplicationSideLogger = std::shared_ptr<spdlog::logger>(spdlog::stdout_color_mt("APP").get());
        mApplicationSideLogger->set_level(spdlog::level::trace);

    }

}