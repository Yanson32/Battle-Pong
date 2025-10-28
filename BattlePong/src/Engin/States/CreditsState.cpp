#include "Engin/States/CreditsState.h"
#include "Engin/States/IntroState.h"
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
#include "Gui/PlayPanel.h"
#include "Gui/GuiId.h"
#include <GameUtilities/Event/Events/OnLog.h>
#include <GameUtilities/Core/Macros.h>
#include "Log.h"
#include "Gui/CreditsPanel.h"
#include "SFMLFunctions.h"



CreditsState::CreditsState(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow, DebugDraw &debugDraw, tgui::Gui &newGui, const StateId newId): StateBase(newEngin, newWindow, debugDraw, newGui, newId)
{
  BP_LOG_TRACE(__FUNCTION__)
}

void CreditsState::handleEvents(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
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

void CreditsState::update(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
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
        if(creditsTimer.getElapsedTime().asSeconds() >= Settings::creditsTime)
        {
            ++creditsCounter;
            if(creditsCounter >= MAX_CREDITS)
                creditsCounter = 0; 
            creditsTimer.restart();
            credits();
        }
        debugDraw.update();
        pongFrame->ball->update();
        pongFrame->ground->update();
        pongFrame->celing->update();
        pongFrame->leftWall->update();
        pongFrame->rightWall->update();
        pongFrame->leftPaddle->update();
        pongFrame->rightPaddle->update();

    }


}

void CreditsState::draw(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
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

void CreditsState::init(GU::Engin::Engin& engin, std::shared_ptr<GU::Engin::Frame> frame)
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
    
/*    
    ResourceManager::loadTexture(textureId::CREDIT_LAURENT, Credit_Laurent_Gomila_png, Credit_Laurent_Gomila_png_len);
    ResourceManager::loadTexture(textureId::CREDIT_BRUNO, Credit_Bruno_Van_de_Velde_png, Credit_Bruno_Van_de_Velde_png_len);
    float width  = window.getView().getSize().x / 2;
    float height = window.getView().getSize().y / 2;
    m_creditsPanel.setSize(width, height);
    m_creditsPanel.setOrigin(width / 2, height / 2);
    m_creditsPanel.setPosition(window.getView().getCenter().x, window.getView().getCenter().y);
    m_creditsPanel.setBackgroundColor(sf::Color(0, 0, 0, 150));
    m_creditsPanel.add(ResourceManager::get(textureId::CREDIT_LAURENT));
    m_creditsPanel.add(ResourceManager::get(textureId::CREDIT_BRUNO));
*/

    //Load ball sound
    ResourceManager::loadSound(soundId::BALL, "BallCollision.ogg");


    centerText(frame);
    
    textArea = tgui::TextArea::create();
    sf::Vector2f winSize;
    winSize.y = window.getSize().y;
    winSize.x = window.getSize().x;
    textArea->setSize(winSize.x / 2, winSize.y / 4);
    textArea->setPosition(winSize.x / 4, winSize.y / 3);
    textArea->setReadOnly(true);
    textArea->onCaretPositionChange([](){});
    tgui::TextAreaRenderer *renderer = textArea->getSharedRenderer();
    renderer->setBackgroundColor(sf::Color(0, 0, 0, 150));
    renderer->setTextColor(Settings::textColor);
    textArea->setText("Developer: Wayne J Larson Jr\nProject: " + Settings::title.toAnsiString() + "\nWeb: https://github.com/Yanson32/Battle-Pong");
    renderer->setTextSize(winSize.x / 50);
    gui.add(textArea);
    centerText(frame);

}

void CreditsState::clean(std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    UNUSED(frame);
    gui.removeAllWidgets();

    //Remove ball sound
    if(ResourceManager::isLoaded(soundId::BALL))
        ResourceManager::remove(soundId::BALL);
}

void CreditsState::sfEvent(GU::Engin::Engin& engin, const sf::Event &event, std::shared_ptr<GU::Engin::Frame> frame)
{
    UNUSED(engin);

    switch(event.type)
    {
        case sf::Event::KeyPressed:
        {
            if(event.key.code == toKey(Settings::keyboardControlRight))
            {
                ++creditsCounter;
                if(creditsCounter >= MAX_CREDITS)
                    creditsCounter = 0; 
                creditsTimer.restart();
                credits();
                
            }
            else if(event.key.code == toKey(Settings::keyboardControlLeft))
            {
                --creditsCounter;
                if(creditsCounter < 0)
                    creditsCounter = MAX_CREDITS - 1;
                
                creditsTimer.restart();
                credits();
           
            }
            
            else if(event.key.code == toKey(Settings::keyboardControlMenu))
            {
                Game *game = static_cast<Game*>(&engin);
                game->setPop(true);
            }
        }
        break;
        case sf::Event::Resized:
        {
            sf::Vector2f winSize;
            winSize.y = window.getSize().y;
            winSize.x = window.getSize().x;
            textArea->setSize(winSize.x / 2, winSize.y / 4);
            textArea->setPosition(winSize.x / 4, winSize.y / 3);
            tgui::TextAreaRenderer *renderer = textArea->getSharedRenderer();
            renderer->setTextSize(winSize.x / 50);
            
        }
        break;
        default:
            break;
    }


}

void CreditsState::credits()
{
    if(creditsCounter == 0)
    {
        textArea->setText("Developer: Wayne J Larson Jr\nProject: " + Settings::title.toAnsiString() + "\nWeb: https://github.com/Yanson32/Battle-Pong");
    }
    else if(creditsCounter == 1)
    {
        textArea->setText("Developer: Bruno Van de Velde\nProject: TGUI\nWeb: https://tgui.eu/");
    }
    else if(creditsCounter == 2)
    {
        textArea->setText("Developer: Erin Catto\nProject: BOX2D\nWeb: https://box2d.org/");
    }
    else if(creditsCounter == 3)
    {
        textArea->setText("Developer: Laurent Gomila\nProject: SFML\nWeb: https://www.sfml-dev.org/");
    }

} 
void CreditsState::handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event, std::shared_ptr<GU::Engin::Frame> frame)
{
    StateBase::handleGUEvent(engin, event, frame);
}

CreditsState::~CreditsState()
{
  BP_LOG_TRACE(__FUNCTION__)
}
