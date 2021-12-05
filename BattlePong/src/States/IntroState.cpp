        
        
        
#include "States/IntroState.h"
#include "GameUtilities/Engin/Engin.h"
#include <GameUtilities/Event/Event.h>
#include <GameUtilities/Event/EventQueue.h>
#include <GameUtilities/Event/PushState.h>
#include <GameUtilities/Event/Click.h>
//#include <GameUtilities/Event/LogEvent.h>
//#include <GameUtilities/Event/LogType.h>

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
#include "GameUtilities/Event/PlaySound.h"


#include "Resources/ResourceManager.h"
#include "Logging.h"
#include "Macros.h"
#include "Gui/IntroState/IntroGui.h"
#include "Gui/IntroState/OptionsPanel.h"
#include "Gui/ButtonId.h"
#include "Gui/IntroState/ControlPanel.h"
#include "Gui/IntroState/DevPanel.h"
#include "Gui/IntroState/SoundPanel.h"
#include "Gui/IntroState/GeneralPanel.h"
#include "Gui/IntroState/MultiplayerPanel.h"
#include "Gui/IntroState/HostPanel.h"
#include "Gui/IntroState/ConnectPanel.h"
#include "Gui/IntroState/VideoPanel.h"
#include "Gui/IntroState/NetworkPanel.h"


#include "Resources/SoundId.h"
#include "Resources/MusicId.h"

#include <memory>
IntroState::IntroState(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow, DebugDraw &debugDraw, tgui::Gui &newGui): StateBase(newEngin, newWindow, debugDraw, newGui, StateId::INTRO_STATE)
{

    //ctor
}


void IntroState::HandleEvents(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{
    UNUSED(deltaTime);
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       //GU::Evt::LogEvent("Pointer should not be null", GU::Evt::LogType::ERROR); 
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
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       //GU::Evt::LogEvent("Pointer should not be null", GU::Evt::LogType::ERROR); 
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
}

void IntroState::Draw(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       //GU::Evt::LogEvent("Pointer should not be null", GU::Evt::LogType::ERROR); 
       return;
    }        
	StateBase::Draw(engin, deltaTime, frame);
	window.draw(*pongFrame->ball);
	window.draw(header);
    window.display();
}



void IntroState::Init(std::shared_ptr<GU::Engin::Frame> frame)
{

    std::cout << "IntroState Init" << std::endl;
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       //GU::Evt::LogEvent("Pointer should not be null", GU::Evt::LogType::ERROR); 
       return;
    }        
    Settings::stateId = StateId::INTRO_STATE; 
    StateBase::Init(frame);
    
    pongFrame->ball->setPosition({400, 300});
    pongFrame->ball->setVelocity({100, 100});
    pongFrame->leftPaddle->setPosition(sf::Vector2f(100, 300));
    pongFrame->rightPaddle->setPosition(sf::Vector2f(700, 300));

    header.setString(Settings::window.title);
    header.setCharacterSize(54);
    header.setFillColor(sf::Color::White);
    header.setPosition(sf::Vector2f(335, 25));
    header.setStyle(sf::Text::Bold);
        
    
    std::shared_ptr<IntroGui> cust(new IntroGui());
    cust->init(window.getView().getSize().x, window.getView().getSize().y); 
    gui.add(cust, "PanelPointer");
  
    //Load ball collision sound  
    if(!ResourceManager::sound.isLoaded(soundId::BALL))
        ResourceManager::sound.load(soundId::BALL, sf::String("Resources/Sounds/BallCollision.ogg"));

   

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
    gui.removeAllWidgets();
    
//    ResourceManager::sound.remove(Sound::Id::MESSAGE);
//    ResourceManager::sound.remove(Sound::Id::BUTTON);
//    ResourceManager::font.remove("Header Font");

}

void IntroState::sfEvent(GU::Engin::Engin& engin, const sf::Event &event, std::shared_ptr<GU::Engin::Frame> frame)
{
    StateBase::sfEvent(engin, event, frame);
    switch(event.type)
    {
        case sf::Event::JoystickConnected: 
            std::cout  << "Joystick connected" << std::endl; 
            break;
        case sf::Event::JoystickDisconnected:
            std::cout << "Joystick Disconnected" << std::endl;
            break;
        case sf::Event::JoystickButtonPressed:
            std::cout << "Joystick Button Pressed" << std::endl;
            break;
        case sf::Event::JoystickButtonReleased:
            std::cout << "Joystick Button Released" << std::endl;
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

        defualt:
           break;   
    };
}

void IntroState::handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event, std::shared_ptr<GU::Engin::Frame> frame)
{
    StateBase::handleGUEvent(engin, event, frame);
}

IntroState::~IntroState()
{
    //dtor


}
