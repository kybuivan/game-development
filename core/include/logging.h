#ifndef __LOGGING_H__
#define __LOGGING_H__

#define DEFAULT_LOGGER_NAME "Logging"
#define DEFAULT_LOG_PATTERN   "[%l][%H:%M:%S.%e] %v"
#define DEFAULT_LOG_FILE_NAME "logs/session_log.log"
#define LOG_FILES_PER_SESSION 5
#define LOGGER_ENABLED

#if defined (LOGGER_ENABLED)

#include <vector>
#include <string>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

class LogManager final
{
  private:
    std::vector<spdlog::sink_ptr> m_sinks;

  public:
    inline void Init() noexcept
    {
        try
        {
            auto fileSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            //auto fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(DEFAULT_LOG_FILE_NAME, 1024 * 1024, LOG_FILES_PER_SESSION, false);
            fileSink->set_pattern(DEFAULT_LOG_PATTERN);

            m_sinks.insert(m_sinks.begin(), fileSink);

            auto logger = std::make_shared<spdlog::logger>(DEFAULT_LOGGER_NAME, fileSink);
            spdlog::set_default_logger(logger);
            logger->set_level(spdlog::level::trace);
            logger->flush_on(spdlog::level::trace);

            logger->trace(__DATE__);
        }
        catch (const spdlog::spdlog_ex &e)
        {
        }
    }

    inline void Release() noexcept
    {
        spdlog::shutdown();
    }

    inline void AddLogger() noexcept
    {
    }

    inline void RemoveLogger() noexcept
    {
    }
};

#define FATAL(...)   if (spdlog::get(DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(DEFAULT_LOGGER_NAME)->critical(__VA_ARGS__);}
#define ERROR(...)      if (spdlog::get(DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(DEFAULT_LOGGER_NAME)->error(__VA_ARGS__);}
#define WARN(...)       if (spdlog::get(DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(DEFAULT_LOGGER_NAME)->warn(__VA_ARGS__);}
#define INFO(...)       if (spdlog::get(DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(DEFAULT_LOGGER_NAME)->info(__VA_ARGS__);}
#define DEBUG(...)      if (spdlog::get(DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(DEFAULT_LOGGER_NAME)->debug(__VA_ARGS__);}
#define TRACE(...)      if (spdlog::get(DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(DEFAULT_LOGGER_NAME)->trace(__VA_ARGS__);}
#else
#define FATAL(msg)   (void)0
#define ERROR(msg)   (void)0
#define WARN(msg)    (void)0
#define INFO(msg)    (void)0
#define DEBUG(msg)   (void)0
#define TRACE(msg)   (void)0
#endif

#endif //__LOGGING_H__