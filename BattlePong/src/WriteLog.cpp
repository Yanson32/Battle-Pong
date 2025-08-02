#include "WriteLog.h"
#include "Log.h"
#include <GameUtilities/Log/Component/Components.h>
WriteLog::WriteLog(Game &game):m_game(game)

{
    BP_LOG_TRACE(__FUNCTION__);
}

void WriteLog::write(Game &game)
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
                    game.logManager.write(entry);
                    exit(1);
                }
                else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_ERROR))
                    game.logManager.write(entry);
                else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_WARNING))
                    game.logManager.write(entry);
                else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_MESSAGE))
                    game.logManager.write(entry);
                else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_VERBOSE))
                    game.logManager.write(entry);
                else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_STATUS))
                    game.logManager.write(entry);
                else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_SYSTEM_ERROR))
                    game.logManager.write(entry);
                else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_DEBUG))
                    game.logManager.write(entry);
                else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_TRACE))
                    game.logManager.write(entry);

            }
            break;
        }
    }
}

WriteLog::~WriteLog()
{
    BP_LOG_TRACE(__FUNCTION__);
    write(m_game); 
}

