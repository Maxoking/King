//Always include precompiled header first
#include "kngpch.h"

#include "Log.h"


namespace King {
  std::shared_ptr<spdlog::logger> Log::s_coreLogger;
  std::shared_ptr<spdlog::logger> Log::s_clientLogger;
  
  void Log::init() {
    spdlog::set_pattern("%^[%T] %n: %v%$");
    s_coreLogger = spdlog::stdout_color_mt("KING");
    s_coreLogger->set_level(spdlog::level::trace);

    s_clientLogger = spdlog::stdout_color_mt("CLIENT");
    s_clientLogger->set_level(spdlog::level::trace);
  }
}
