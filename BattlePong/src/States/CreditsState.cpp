#include "States/CreditsState.h"
#include "Log.h"
#include "Events/EventManager.h"

CreditsState::CreditsState(GU::Engin::Engin& engin, sf::RenderWindow &newWindow, DebugDraw &debugDraw, tgui::Gui &newGui): StateBase(engin, newWindow, debugDraw, newGui, StateId::CREDITS_STATE)
{
  BP_LOG_TRACE(__FUNCTION__)
}


void CreditsState::HandleEvents(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    UNUSED(deltaTime);
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
        BP_LOG_FATAL_ERROR("The Pointer should not be null");     
        return;
    }


    if(window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            StateBase::sfEvent(engin, event, frame);
            sfEvent(engin, event, frame);
            gui.handleEvent(event);
        }

    }

    //GameUtilities event loop
    GU::Evt::EventPtr evtPtr;
    while(EventManager::inst().Poll((evtPtr)))
    {
        handleGUEvent(engin, evtPtr, pongFrame);
    }
}


void CreditsState::Update(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{
  BP_LOG_TRACE(__FUNCTION__)
}


void CreditsState::Draw(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    window.clear();

    window.display(); 
}


void CreditsState::handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event, std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
}


void CreditsState::sfEvent(GU::Engin::Engin& engin, const sf::Event &event, std::shared_ptr<GU::Engin::Frame> frame)
{
  BP_LOG_TRACE(__FUNCTION__)
}


void CreditsState::Init(std::shared_ptr<GU::Engin::Frame> frame)
{
  BP_LOG_TRACE(__FUNCTION__)
}


void CreditsState::Clean(std::shared_ptr<GU::Engin::Frame> frame)
{
  BP_LOG_TRACE(__FUNCTION__)
}

CreditsState::~CreditsState()
{
  BP_LOG_TRACE(__FUNCTION__)
}
