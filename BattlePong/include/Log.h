#ifndef LOG_H
#define LOG_H
/*************************************************************************
*                           COPYRIGHT NOTICE
* Battle Pong is a clone of the classic pong game.
* Copyright (C) 2017 Wayne J Larson Jr. 
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 3 as 
* published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
***************************************************************************/
#include <GameUtilities/Event/LogEvent.h>
#define BP_LOG_FATAL_ERROR(x)(EventManager::inst().post<GU::Evt::LogEvent>(x, static_cast<int>(GU::Log::LogType::GU_FATAL_ERROR), int(__LINE__), GU::Core::String(__FILE__)));
#define BP_LOG_ERROR(x)(EventManager::inst().post<GU::Evt::LogEvent>(x, static_cast<int>(GU::Log::LogType::GU_ERROR), int(__LINE__), GU::Core::String(__FILE__)));
#define BP_LOG_WARNING(x)(EventManager::inst().post<GU::Evt::LogEvent>(x, static_cast<int>(GU::Log::LogType::GU_WARNING), int(__LINE__), GU::Core::String(__FILE__)));
#define BP_LOG_MESSAGE(x)(EventManager::inst().post<GU::Evt::LogEvent>(x, static_cast<int>(GU::Log::LogType::GU_MESSAGE), int(__LINE__), GU::Core::String(__FILE__)));
#define BP_LOG_VERBOSE(x)(EventManager::inst().post<GU::Evt::LogEvent>(x, static_cast<int>(GU::Log::LogType::GU_VERBOSE), int(__LINE__), GU::Core::String(__FILE__)));
#define BP_LOG_STATUS(x)(EventManager::inst().post<GU::Evt::LogEvent>(x, static_cast<int>(GU::Log::LogType::GU_STATUS), int(__LINE__), GU::Core::String(__FILE__)));
#define BP_LOG_SYSTEM_ERROR(x)(EventManager::inst().post<GU::Evt::LogEvent>(x, static_cast<int>(GU::Log::LogType::GU_SYSTEM_ERROR), int(__LINE__), GU::Core::String(__FILE__)));
#define BP_LOG_DEBUG(x)(EventManager::inst().post<GU::Evt::LogEvent>(x, static_cast<int>(GU::Log::LogType::GU_DEBUG), int(__LINE__), GU::Core::String(__FILE__)));
#define BP_LOG_TRACE(x)(EventManager::inst().post<GU::Evt::LogEvent>(x, static_cast<int>(GU::Log::LogType::GU_TRACE), int(__LINE__), GU::Core::String(__FILE__)));

#endif
