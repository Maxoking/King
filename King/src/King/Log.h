#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace King {
  class KING_API Log {
  public:
    static void init();

    inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger; };
    inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger; };

  private:
    static std::shared_ptr<spdlog::logger> s_coreLogger;
    static std::shared_ptr<spdlog::logger> s_clientLogger;

  };
}

//Core log macros
#define KING_CORE_TRACE(...)    King::Log::getCoreLogger()->trace(__VA_ARGS__)
#define KING_CORE_ERROR(...)    King::Log::getCoreLogger()->error(__VA_ARGS__)
#define KING_CORE_INFO(...)     King::Log::getCoreLogger()->info(__VA_ARGS__)
#define KING_CORE_WARN(...)     King::Log::getCoreLogger()->warn(__VA_ARGS__)
#define KING_CORE_FATAL(...)    King::Log::getCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define KING_TRACE(...)     King::Log::getClientLogger()->trace(__VA_ARGS__)
#define KING_ERROR(...)     King::Log::getClientLogger()->error(__VA_ARGS__)
#define KING_INFO(...)      King::Log::getClientLogger()->info(__VA_ARGS__)
#define KING_WARN(...)      King::Log::getClientLogger()->warn(__VA_ARGS__)
#define KING_FATAL(...)     King::Log::getClientLogger()->fatal(__VA_ARGS__)




