#include "States/IntroState.h"
#include "GameUtilities/Engin/Engin.h"
#include <GameUtilities/Event/Event.h>
#include <GameUtilities/Event/EventQueue.h>
#include <GameUtilities/Event/PushState.h>
#include <GameUtilities/Event/Click.h>
#include <GameUtilities/Event/OnComboChanged.h>

#include <GameUtilities/Event/LogEvent.h>
#include <GameUtilities/Log/LogType.h>
#include "GameUtilities/Event/PlaySound.h"
#include <GameUtilities/Core/Macros.h>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <SFML/Graphics/Font.hpp>

#include "States/PlayState.h"
#include "Settings.h"

#include "Objects/Wall.h"
#include "Objects/Ball.h"
#include "Objects/Paddle.h"
#include "Objects/PongFrame.h"
#include "States/StateId.h"
#include "Events/EventManager.h"



#include "Resources/ResourceManager.h"
#include "Macros.h"
#include "Gui/InfoPanel/InfoPanel.h"
#include "Gui/InfoPanel/OptionsPanel.h"
#include "Gui/InfoPanel/ControlPanel.h"
#include "Gui/InfoPanel/DevPanel.h"
#include "Gui/InfoPanel/SoundPanel.h"
#include "Gui/InfoPanel/GeneralPanel.h"
#include "Gui/InfoPanel/MultiplayerPanel.h"
#include "Gui/InfoPanel/HostPanel.h"
#include "Gui/InfoPanel/ConnectPanel.h"
#include "Gui/InfoPanel/VideoPanel.h"
#include "Gui/InfoPanel/NetworkPanel.h"
#include "Gui/ButtonId.h"
#include "Gui/ComboId.h"
#include <iostream>
#include <filesystem>

#include "Resources/SoundId.h"
#include "Resources/MusicId.h"
#include "Log.h"
#include <memory>
IntroState::IntroState(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow, DebugDraw &debugDraw, tgui::Gui &newGui): StateBase(newEngin, newWindow, debugDraw, newGui, StateId::INTRO_STATE)
{
    BP_LOG_TRACE(__FUNCTION__)
    //ctor

}


void IntroState::HandleEvents(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    UNUSED(deltaTime);
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       EventManager::inst().Post<GU::Evt::LogEvent>("Pointer should not be null", static_cast<int>(GU::Log::LogType::GU_FATAL_ERROR), int(__LINE__), GU::Core::String(__FILE__));
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
        pongFrame->leftPaddle->handleInput(*pongFrame->ball);
        pongFrame->rightPaddle->handleInput(*pongFrame->ball);
    }

    //GameUtilities event loop
    GU::Evt::EventPtr evtPtr;
    while(EventManager::inst().Poll((evtPtr)))
    {
        handleGUEvent(engin, evtPtr, pongFrame);
    }

}

void IntroState::Update(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       EventManager::inst().Post<GU::Evt::LogEvent>("Pointer should not be null", static_cast<int>(GU::Log::LogType::GU_FATAL_ERROR), int(__LINE__), GU::Core::String(__FILE__));
       return;
    }

    StateBase::Update(engin, deltaTime, frame);
    pongFrame->world->Step( timeStep, velocityIterations, positionIterations);
    debugDraw.update();
    pongFrame->ball->update();
    pongFrame->ground->update();
    pongFrame->celing->update();
    pongFrame->leftWall->update();
    pongFrame->rightWall->update();
    pongFrame->leftPaddle->update();
    pongFrame->rightPaddle->update();
    header.setPosition({window.getView().getSize().x / 2, window.getView().getSize().y / 6});


}

void IntroState::Draw(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)

    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       EventManager::inst().Post<GU::Evt::LogEvent>("Pointer should not be null", static_cast<int>(GU::Log::LogType::GU_FATAL_ERROR), int(__LINE__), GU::Core::String(__FILE__));
       return;
    }
	StateBase::Draw(engin, deltaTime, frame);
	window.draw(*pongFrame->ball);
	window.draw(header);
	//window.draw(header);
    window.display();
}



void IntroState::Init(std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    StateBase::Init(frame);

    Settings::stateId = StateId::INTRO_STATE;

    //Create pong frame
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       EventManager::inst().Post<GU::Evt::LogEvent>("Pointer should not be null", static_cast<int>(GU::Log::LogType::GU_FATAL_ERROR), int(__LINE__), GU::Core::String(__FILE__));
       return;
    }

    pongFrame->ball->setPosition({400, 300});
    pongFrame->ball->setVelocity({100, 100});
    pongFrame->leftPaddle->setPosition(sf::Vector2f(100, 300));
    pongFrame->rightPaddle->setPosition(sf::Vector2f(700, 300));

    //Create intro panel
    std::shared_ptr<InfoPanel> cust(new InfoPanel());
    cust->init(window.getView().getSize().x, window.getView().getSize().y);
    gui.add(cust, "PanelPointer");

    //Load ball collision sound
    ResourceManager::loadSound(soundId::BALL, "BallCollision.ogg");

    //Load title image
    ResourceManager::loadTexture(textureId::TITLE, "Battle Pong.png");

    //Set title properties
    header.setTexture(ResourceManager::get(textureId::TITLE));
    header.setScale({0.25, 0.25});
    header.setOrigin({960, 540});

//    ResourceManager::sound.load(Sound::Id::MESSAGE, "../Resources/Sounds/tone1.ogg");
//    ResourceManager::sound.load(Sound::Id::BUTTON, "../Resources/Sounds/tone1.ogg");
//    ResourceManager::sound.load(Sound::Id::BALL, "../Resources/Sounds/tone1.ogg");
//    ResourceManager::font.load("Header Font", "../Resources/Fonts/caviar-dreams/CaviarDreams.ttf");
//
//    header.setFont(ResourceManager::font.get("Header Font"));
    reset(pongFrame);
}

void IntroState::Clean(std::shared_ptr<GU::Engin::Frame> frame)
{
  BP_LOG_TRACE(__FUNCTION__)
  gui.removeAllWidgets();

    //Remove ball collision sound
    //if(ResourceManager::isLoaded(soundId::BALL))
        //ResourceManager::remove(soundId::BALL);

    //Remove title image
    //if(ResourceManager::isLoaded(textureId::TITLE))
	    //ResourceManager::remove(textureId::TITLE);

//    ResourceManager::sound.remove(Sound::Id::MESSAGE);
//    ResourceManager::sound.remove(Sound::Id::BUTTON);
//    ResourceManager::font.remove("Header Font");

}

void IntroState::sfEvent(GU::Engin::Engin& engin, const sf::Event &event, std::shared_ptr<GU::Engin::Frame> frame)
{
    StateBase::sfEvent(engin, event, frame);
    switch(event.type)
    {
        case sf::Event::LostFocus:
            BP_LOG_WARNING("Unused case lable triggered");
        break;
        case sf::Event::Closed:
            BP_LOG_WARNING("Unused case lable triggered");
        break;
        case sf::Event::GainedFocus:
            BP_LOG_WARNING("Unused case lable triggered");
        break;
        case sf::Event::TextEntered:
            BP_LOG_WARNING("Unused case lable triggered");
        break;
        case sf::Event::KeyPressed:
            BP_LOG_WARNING("Unused case lable triggered");
        break;
        case sf::Event::KeyReleased:
            BP_LOG_WARNING("Unused case lable triggered");
        break;
        case sf::Event::MouseWheelMoved:
            BP_LOG_WARNING("Unused case lable triggered");
        break;
        case sf::Event::MouseWheelScrolled:
            BP_LOG_WARNING("Unused case lable triggered");
        break;
        case sf::Event::MouseButtonPressed:
            BP_LOG_WARNING("Unused case lable triggered");
        break;
        case sf::Event::MouseButtonReleased:
            BP_LOG_WARNING("Unused case lable triggered");
        break;
        case sf::Event::MouseMoved:
            BP_LOG_WARNING("Unused case lable triggered");
        break;
        case sf::Event::MouseEntered:
            BP_LOG_WARNING("Unused case lable triggered");
        break;
        case sf::Event::MouseLeft:
            BP_LOG_WARNING("Unused case lable triggered");
        break;
        case sf::Event::TouchBegan:
            BP_LOG_WARNING("Unused case lable triggered");
        break;
        case sf::Event::TouchMoved:
            BP_LOG_WARNING("Unused case lable triggered");
        break;
        case sf::Event::TouchEnded:
            BP_LOG_WARNING("Unused case lable triggered");
        break;
        case sf::Event::SensorChanged:
            BP_LOG_WARNING("Unused case lable triggered");
        break;
        case sf::Event::Count:
            BP_LOG_WARNING("Unused case lable triggered");
        break;
        case sf::Event::JoystickConnected:
            BP_LOG_MESSAGE("Joystick connected");
            break;
        case sf::Event::JoystickDisconnected:
            BP_LOG_MESSAGE("Joystick Disconnected");
            break;
        case sf::Event::JoystickButtonPressed:
            BP_LOG_MESSAGE("Joystick Button Pressed");
            break;
        case sf::Event::JoystickButtonReleased:
            BP_LOG_MESSAGE("Joystick Button Released");
            break;
        case sf::Event::JoystickMoved:
            switch(event.joystickMove.axis)
            {
                case sf::Joystick::X:
                case sf::Joystick::Z:
                case sf::Joystick::U:
                case sf::Joystick::PovX:
                if(event.joystickMove.position > 0)
                   std::cout << "Right" << std::endl;
                else if(event.joystickMove.position < 0)
                   std::cout << "Left" << std::endl;
                break;

                case sf::Joystick::Y:
                case sf::Joystick::R:
                case sf::Joystick::V:
                case sf::Joystick::PovY:
                if(event.joystickMove.position > 0)
                    std::cout << "Down" << std::endl;
                else if (event.joystickMove.position < 0)
                    std::cout << "Up" << std::endl;
                break;
            };
	case sf::Event::Resized:
	    break;
    };
}

void IntroState::handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event, std::shared_ptr<GU::Engin::Frame> frame)
{
    StateBase::handleGUEvent(engin, event, frame);
    switch(event->getId())
    {
        case EventId::CLICK:
	      {
            std::shared_ptr<GU::Evt::Click> temp =  std::dynamic_pointer_cast<GU::Evt::Click>(event);
            if(temp)
            {
                switch(temp->buttonId)
                {
                    case Button::id::INTRO_PANEL:
                    break;
		                case Button::id::OPTIONS:
                    case Button::id::GENERAL_TAB:
                    break;
                    case Button::id::CONTROLS_TAB:
                    break;
                    case Button::id::VIDEO_TAB:
                    break;
                    case Button::id::SOUND_TAB:
                    break;
                    case Button::id::NETWORK_TAB:
                    break;
                    case Button::id::DEV_TAB:
                    break;
                    case Button::id::MULTIPLAYER:
                    break;
                    case Button::id::HOST:
                    break;
                    case Button::id::CONNECT:
	            break;
		          }
	         }
	    }
	    break;
        case EventId::ON_COMBO_CHANGED:
            {
    	       //Load title image
    	       if(ResourceManager::isLoaded(textureId::TITLE))
	            ResourceManager::remove(textureId::TITLE);
	           ResourceManager::loadTexture(textureId::TITLE, "Battle Pong.png");
    	       header.setTexture(ResourceManager::get(textureId::TITLE));
            }



	}


}

IntroState::~IntroState()
{
  BP_LOG_TRACE(__FUNCTION__)
    //dtor
}
