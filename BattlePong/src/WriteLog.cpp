#include "WriteLog.h"
#include "Log.h"
#include <GameUtilities/Log/Component/Components.h>
WriteLog::WriteLog(Game &game):m_game(game)

{
    BP_LOG_TRACE(__FUNCTION__);
}



WriteLog::~WriteLog()
{
    BP_LOG_TRACE(__FUNCTION__);
    
    //GameUtilities event loop
    GU::Evt::EventPtr event;
    while(EventManager::inst().poll((event)))
    {

        switch(event->getId())
        {
            case EventId::LOG:
            {
                std::shared_ptr<GU::Evt::OnLog> temp =  std::dynamic_pointer_cast<GU::Evt::OnLog>(event);
                std::shared_ptr<GU::Log::LogEntry> entry(new GU::Log::LogEntry());
                entry->add<GU::Log::MsgComponent>(temp->getMessage());
                entry->add<GU::Log::SeverityComponent>(static_cast<GU::Log::LogType>(temp->getSeverity()));
                entry->add<GU::Log::LineComponent>(temp->getLine());
                entry->add<GU::Log::FileComponent>(temp->getFile());

                if(temp->getSeverity() > Settings::logSeverity)
                    return;

                if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_FATAL_ERROR))
                {
                    m_game.logManager.write(entry);
                    exit(1);
                }
                else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_ERROR))
                    m_game.logManager.write(entry);
                else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_WARNING))
                    m_game.logManager.write(entry);
                else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_MESSAGE))
                    m_game.logManager.write(entry);
                else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_VERBOSE))
                    m_game.logManager.write(entry);
                else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_STATUS))
                    m_game.logManager.write(entry);
                else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_SYSTEM_ERROR))
                    m_game.logManager.write(entry);
                else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_DEBUG))
                    m_game.logManager.write(entry);
                else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_TRACE))
                    m_game.logManager.write(entry);

            }
            break;
        }
    }
}

