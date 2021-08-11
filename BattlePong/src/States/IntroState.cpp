#include "States/IntroState.h"
#include "GameUtilities/Engin/Engin.h"
#include <GameUtilities/Event/Event.h>
#include <GameUtilities/Event/EventQueue.h>
#include <GameUtilities/Event/PushState.h>
#include <GameUtilities/Event/Click.h>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <SFML/Graphics/Font.hpp>

#include "States/PlayState.h"
#include "Settings.h"

#include "Objects/Wall.h"
#include "Objects/Ball.h"
#include "Objects/Paddle.h"
#include "States/Id.h"
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
IntroState::IntroState(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow, std::shared_ptr<Frame> newFrame): StateBase(newEngin, newWindow, newFrame, stateId::INTRO_STATE)
{

    //ctor
    frame->ball->setPosition({400, 300});
    frame->ball->setVelocity({100, 100});
    frame->leftPaddle->setPosition(sf::Vector2f(100, 300));
    frame->rightPaddle->setPosition(sf::Vector2f(700, 300));

    header.setString(Settings::window.title);
    header.setCharacterSize(54);
    header.setFillColor(sf::Color::White);
    header.setPosition(sf::Vector2f(335, 25));
    header.setStyle(sf::Text::Bold);

}


void IntroState::HandleEvents(GU::Engin::Engin& engin, const float &deltaTime)
{
    UNUSED(deltaTime);
    if(window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            StateBase::sfEvent(engin, event);
            sfEvent(engin, event);
            gui.handleEvent(event);
        }
        frame->leftPaddle->handleInput(*frame->ball);
        frame->rightPaddle->handleInput(*frame->ball);
    }

    //GameUtilities event loop
    GU::Evt::EventPtr evtPtr;
    while(EventManager::inst().Poll((evtPtr)))
    {
        handleGUEvent(engin, evtPtr);
    }

}

void IntroState::Update(GU::Engin::Engin& engin, const float &deltaTime)
{
    StateBase::Update(engin, deltaTime);
    frame->world->Step( timeStep, velocityIterations, positionIterations);
    debugDraw->update();
    frame->ball->update();
    frame->ground->update();
    frame->celing->update();
    frame->leftWall->update();
    frame->rightWall->update();
    frame->leftPaddle->update();
    frame->rightPaddle->update();
}

void IntroState::Draw(GU::Engin::Engin& engin, const float &deltaTime)
{
	StateBase::Draw(engin, deltaTime);
	window.draw(*frame->ball);
	window.draw(header);
    window.display();
}



void IntroState::Init()
{
    StateBase::Init();
    tgui::Panel::Ptr cust(new IntroGui());
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
    reset();
}

void IntroState::Clean()
{
    gui.removeAllWidgets();
    
//    ResourceManager::sound.remove(Sound::Id::MESSAGE);
//    ResourceManager::sound.remove(Sound::Id::BUTTON);
//    ResourceManager::font.remove("Header Font");

}


void IntroState::handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event)
{
    StateBase::handleGUEvent(engin, event);


    switch(event->id)
    {
        case EventId::CLICK:
            std::shared_ptr<GU::Evt::Click> temp =  std::dynamic_pointer_cast<GU::Evt::Click>(event);
            if(temp)
            {
                switch(temp->buttonId)
                {
                    case Button::id::START:
                        engin.Push<PlayState>(engin, window, frame);
                    break;
                    case Button::id::INTRO_PANEL:
                    {
                        gui.removeAllWidgets();
                        StateBase::Init();
                        tgui::Panel::Ptr cust(new IntroGui());
                        std::shared_ptr<IntroGui> p = std::dynamic_pointer_cast<IntroGui>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");

                    }
                    break;
                    case Button::id::GENERAL_TAB:
                    {
                        gui.removeAllWidgets();
                        StateBase::Init();
                        tgui::Panel::Ptr cust(new Gui::GeneralPanel());
                        std::shared_ptr<Gui::GeneralPanel> p = std::dynamic_pointer_cast<Gui::GeneralPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                    }
                    break;
                    case Button::id::CONTROLS_TAB:
                    {
                        gui.removeAllWidgets();
                        StateBase::Init();
                        tgui::Panel::Ptr cust(new Gui::ControlPanel(nullptr));
                        std::shared_ptr<Gui::ControlPanel> p = std::dynamic_pointer_cast<Gui::ControlPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                    }
                    break;
                    case Button::id::VIDEO_TAB:
                     {
                        gui.removeAllWidgets();
                        StateBase::Init();
                        tgui::Panel::Ptr cust(new Gui::VideoPanel());
                        std::shared_ptr<Gui::VideoPanel> p = std::dynamic_pointer_cast<Gui::VideoPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                    }
                    break;
                    case Button::id::SOUND_TAB:
                     {
                        gui.removeAllWidgets();
                        StateBase::Init();
                        tgui::Panel::Ptr cust(new Gui::SoundPanel(nullptr));
                        std::shared_ptr<Gui::SoundPanel> p = std::dynamic_pointer_cast<Gui::SoundPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                    }
                    break;
                    case Button::id::NETWORK_TAB:
                     {
                        gui.removeAllWidgets();
                        StateBase::Init();
                        tgui::Panel::Ptr cust(new Gui::NetworkPanel());
                        std::shared_ptr<Gui::NetworkPanel> p = std::dynamic_pointer_cast<Gui::NetworkPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                    }
                    break;
                    case Button::id::DEV_TAB:
                     {
                        gui.removeAllWidgets();
                        StateBase::Init();
                        tgui::Panel::Ptr cust(new Gui::DevPanel());
                        std::shared_ptr<Gui::DevPanel> p = std::dynamic_pointer_cast<Gui::DevPanel>(cust);
                        p->init(debugDraw->GetFlags(), window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                    }
                    break;
                    case Button::id::MULTIPLAYER:
                     {
                        gui.removeAllWidgets();
                        StateBase::Init();
                        tgui::Panel::Ptr cust(new MultiplayerPanel());
                        std::shared_ptr<MultiplayerPanel> p = std::dynamic_pointer_cast<MultiplayerPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                    }
                    break;
                    case Button::id::HOST:
                     {
                        gui.removeAllWidgets();
                        StateBase::Init();
                        tgui::Panel::Ptr cust(new HostPanel());
                        std::shared_ptr<HostPanel> p = std::dynamic_pointer_cast<HostPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                     }
                    break;
                    case Button::id::CONNECT:
                    {
                        gui.removeAllWidgets();
                        StateBase::Init();
                        tgui::Panel::Ptr cust(new ConnectPanel());
                        std::shared_ptr<ConnectPanel> p = std::dynamic_pointer_cast<ConnectPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y); 
                        gui.add(cust, "PanelPointer");
                        
                    }
                    break;
                }
            }

        break;
    }
}

IntroState::~IntroState()
{
    //dtor


}
