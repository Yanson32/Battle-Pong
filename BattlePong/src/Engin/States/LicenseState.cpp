#include "Engin/States/LicenseState.h"
#include "Objects/Ball.h"
#include <SFML/Window/Event.hpp>
#include "Engin/Game.h"
#include <Box2D/Box2D.h>
#include <iostream>
#include "Box2D/Box2DFunctions.h"
#include <SFML/Graphics/CircleShape.hpp>

#include "Objects/Wall.h"
#include "Objects/Paddle.h"
#include "Input/AI.h"
#include "Settings.h"
#include "Resources/ResourceManager.h"
#include "Events/Events.h"
#include "Macros.h"
#include "Gui/GuiId.h"
#include <GameUtilities/Event/Events/OnLog.h>
#include <GameUtilities/Core/Macros.h>
#include "Log.h"
#include "SFMLFunctions.h"
#include "Resources/License.h"

LicenseState::LicenseState(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow, DebugDraw &debugDraw, tgui::Gui &newGui, const StateId newId): StateBase(newEngin, newWindow, debugDraw, newGui, newId)
{
  BP_LOG_TRACE(__FUNCTION__)
}

void LicenseState::handleEvents(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    UNUSED(deltaTime);

    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
      BP_LOG_FATAL_ERROR("Pointer should not be null")
      return;
    }
    if(window.isOpen())
    {
        sf::Event event;
        BP_LOG_MESSAGE("SFML Event Loop")
        while (window.pollEvent(event))
        {
            StateBase::sfEvent(engin, event, frame);
            sfEvent(engin, event, frame);
            gui.handleEvent(event);
        }
        pongFrame->leftPaddle->handleInput(*pongFrame->ball);
        pongFrame->rightPaddle->handleInput(*pongFrame->ball);
    }
    
    //GameUtilities event loop
    GU::Evt::EventPtr evtPtr;
    while(EventManager::inst().poll((evtPtr)))
    {
        handleGUEvent(engin, evtPtr, frame);
    }
}

void LicenseState::update(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       BP_LOG_FATAL_ERROR("Pointer should not be null")
       return;
    }
    const int SECONDS = 1;

    StateBase::update(engin, deltaTime, frame);

    if(!Settings::playerPaused)
    {
        if(!Settings::systemPaused)
        {
            pongFrame->world->Step( deltaTime, Settings::velocityIterations, Settings::positionIterations);
        }
        debugDraw.update();
        pongFrame->update(engin, deltaTime);
        pongFrame->ball->update();
        pongFrame->ground->update();
        pongFrame->celing->update();
        pongFrame->leftWall->update();
        pongFrame->rightWall->update();
        pongFrame->leftPaddle->update();
        pongFrame->rightPaddle->update();

    }

}

void LicenseState::draw(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       BP_LOG_FATAL_ERROR("Pointer should not be null")
       return;
    }
    StateBase::draw(engin, deltaTime, frame);
    window.draw(*pongFrame->ball);
    window.draw(pongFrame->userMessage[pongFrame->userMessageIndex]);
    window.display();

}

void LicenseState::init(GU::Engin::Engin& engin, std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    UNUSED(frame);

    StateBase::init(engin, frame);
    Settings::stateId = StateId::CREDITS_STATE;

    //Crate pong frame
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       BP_LOG_FATAL_ERROR("Pointer should not be null")
       return;
    }
    
    
    //Load ball sound
    ResourceManager::loadSound(soundId::BALL, "BallCollision.ogg");

    textArea = tgui::TextArea::create();
    textArea->setText(license);
    sf::Vector2f winSize;
    winSize.y = window.getSize().y;
    winSize.x = window.getSize().x;
    textArea->setSize(winSize.x / 2, winSize.y / 2);
    textArea->setPosition(winSize.x / 4, winSize.y / 4);
    textArea->setReadOnly(true);
    textArea->onCaretPositionChange([](){});
    tgui::TextAreaRenderer *renderer = textArea->getSharedRenderer();
    renderer->setBackgroundColor(sf::Color(0, 0, 0, 150));
    renderer->setTextColor(Settings::textColor);
    renderer->setTextSize(15);
    gui.add(textArea);
    centerText(frame);

}

void LicenseState::clean(std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    UNUSED(frame);
    gui.removeAllWidgets();

    //Remove ball sound
    if(ResourceManager::isLoaded(soundId::BALL))
        ResourceManager::remove(soundId::BALL);
}

void LicenseState::sfEvent(GU::Engin::Engin& engin, const sf::Event &event, std::shared_ptr<GU::Engin::Frame> frame)
{
    UNUSED(engin);

    switch(event.type)
    {
        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::Escape)
            {
                Game *game = static_cast<Game*>(&engin);
                game->setPop(true);
            }
            break;
        default:
            break;
    }


}

void LicenseState::handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event, std::shared_ptr<GU::Engin::Frame> frame)
{
    StateBase::handleGUEvent(engin, event, frame);
}

LicenseState::~LicenseState()
{
  BP_LOG_TRACE(__FUNCTION__)
}
