#include "Game.h"
#include <memory>
#include "Events/Events.h"
#include <GameUtilities/Log/Target/LogFileTarget.h>
#include <GameUtilities/Log/LogFormatter.h>
#include <GameUtilities/Log/Component/Components.h>
Game::Game(): GU::Engin::Engin(),
GU::Evt::EventManager()
{
  //Set log target
  std::shared_ptr<GU::Log::LogTarget> target(new GU::Log::LogFileTarget("log.txt"));
  logManager.add(target);

  //Set log formatter
  GU::Log::LogFormatter logFormatter;
  logFormatter.add<GU::Log::SeverityComponent>();
  logFormatter.add<GU::Log::LineComponent>();
  logFormatter.add<GU::Log::FileComponent>();
  logFormatter.add<GU::Log::MsgComponent>();
  logManager.set(logFormatter);

}

void Game::setPop(const bool pop)
{
    m_pop = pop;
}

bool Game::getPop() const
{
    return m_pop;
}

Game::~Game()
{

}

