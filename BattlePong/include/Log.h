#ifndef LOG_H
#define LOG_H
#include <GameUtilities/Event/LogEvent.h>
#define BP_LOG_FATAL_ERROR(x)(EventManager::inst().Post<GU::Evt::LogEvent>(x, static_cast<int>(GU::Log::LogType::GU_FATAL_ERROR), int(__LINE__), GU::Core::String(__FILE__)));
#define BP_LOG_ERROR(x)(EventManager::inst().Post<GU::Evt::LogEvent>(x, static_cast<int>(GU::Log::LogType::GU_ERROR), int(__LINE__), GU::Core::String(__FILE__)));
#define BP_LOG_WARNING(x)(EventManager::inst().Post<GU::Evt::LogEvent>(x, static_cast<int>(GU::Log::LogType::GU_WARNING), int(__LINE__), GU::Core::String(__FILE__)));
#define BP_LOG_MESSAGE(x)(EventManager::inst().Post<GU::Evt::LogEvent>(x, static_cast<int>(GU::Log::LogType::GU_MESSAGE), int(__LINE__), GU::Core::String(__FILE__)));
#define BP_LOG_VERBOSE(x)(EventManager::inst().Post<GU::Evt::LogEvent>(x, static_cast<int>(GU::Log::LogType::GU_VERBOSE), int(__LINE__), GU::Core::String(__FILE__)));
#define BP_LOG_STATUS(x)(EventManager::inst().Post<GU::Evt::LogEvent>(x, static_cast<int>(GU::Log::LogType::GU_STATUS), int(__LINE__), GU::Core::String(__FILE__)));
#define BP_LOG_SYSTEM_ERROR(x)(EventManager::inst().Post<GU::Evt::LogEvent>(x, static_cast<int>(GU::Log::LogType::GU_SYSTEM_ERROR), int(__LINE__), GU::Core::String(__FILE__)));
#define BP_LOG_DEBUG(x)(EventManager::inst().Post<GU::Evt::LogEvent>(x, static_cast<int>(GU::Log::LogType::GU_DEBUG), int(__LINE__), GU::Core::String(__FILE__)));
#define BP_LOG_TRACE(x)(EventManager::inst().Post<GU::Evt::LogEvent>(x, static_cast<int>(GU::Log::LogType::GU_TRACE), int(__LINE__), GU::Core::String(__FILE__)));

#endif
