#include "States/IntroState.h"
#include "GameUtilities/Engin/Engin.h"
#include <GameUtilities/Event/Event.h>
#include <GameUtilities/Event/EventQueue.h>
#include <GameUtilities/Event/PushState.h>

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


#include "ResourceManager.h"
#include "Logging.h"
#include "Macros.h"
#include "Sounds/Id.h"
#include "Gui/IntroGui.h"
#include "Events/Click.h"
#include "Gui/OptionsPanel.h"
#include "Gui/ButtonId.h"
#include "Gui/ControlPanel.h"
#include "Gui/DevPanel.h"
#include "Gui/SoundPanel.h"
#include "Gui/GeneralPanel.h"
#include "Gui/MultiplayerPanel.h"
#include "Gui/HostPanel.h"

#include <memory>
IntroState::IntroState(GU::Engin::Engin& newEngin): StateBase(newEngin, stateId::INTRO_STATE)
{

    //ctor
    ball->setPosition({400, 300});
    ball->setVelocity({100, 100});
    leftPaddle->setPosition(sf::Vector2f(100, 300));
    rightPaddle->setPosition(sf::Vector2f(700, 300));

    header.setString(Settings::window.title);
    header.setCharacterSize(54);
    header.setFillColor(sf::Color::White);
    header.setPosition(sf::Vector2f(335, 25));
    header.setStyle(sf::Text::Bold);

        tgui::Panel::Ptr cust(new IntroGui());
    gui.add(cust);
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
        leftPaddle->handleInput(*ball);
        rightPaddle->handleInput(*ball);
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
    world->Step( timeStep, velocityIterations, positionIterations);
    debugDraw.update();
    ball->update();
    ground->update();
    celing->update();
    leftWall->update();
    RightWall->update();
    leftPaddle->update();
    rightPaddle->update();
}

void IntroState::Draw(GU::Engin::Engin& engin, const float &deltaTime)
{
	window.draw(*ball);
	StateBase::Draw(engin, deltaTime);
	window.draw(header);
    window.display();
}



void IntroState::Init()
{
    StateBase::Init();

    tgui::Panel::Ptr cust(new IntroGui());
    gui.add(cust);

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
//    ResourceManager::sound.remove(Sound::Id::BALL);
//    ResourceManager::font.remove("Header Font");

}


void IntroState::handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event)
{
    StateBase::handleGUEvent(engin, event);


    switch(event->id)
    {
        case EventId::CLICK:
            std::shared_ptr<Click> temp =  std::dynamic_pointer_cast<Click>(event);
            if(temp)
            {
                switch(temp->buttonId)
                {
                    case Button::id::START:
                        engin.Push<PlayState>(engin);
                    break;
                    case Button::id::INTRO_PANEL:
                    {
                        gui.removeAllWidgets();
                        StateBase::Init();
                        tgui::Panel::Ptr cust(new IntroGui());
                        gui.add(cust);
                    }
                    break;
                    case Button::id::GENERAL_TAB:
                    {
                        gui.removeAllWidgets();
                        StateBase::Init();
                        tgui::Panel::Ptr cust(new Gui::GeneralPanel(nullptr));
                        std::shared_ptr<Gui::GeneralPanel> p = std::dynamic_pointer_cast<Gui::GeneralPanel>(cust);
                        p->init();
                        gui.add(cust);
                    }
                    break;
                    case Button::id::CONTROLS_TAB:
                        std::cout << "Controls tab" << std::endl;
                    {
                        gui.removeAllWidgets();
                        StateBase::Init();
                        tgui::Panel::Ptr cust(new Gui::ControlPanel(nullptr));
                        std::shared_ptr<Gui::ControlPanel> p = std::dynamic_pointer_cast<Gui::ControlPanel>(cust);
                        p->init();
                        gui.add(cust);
                    }
                    break;
                    case Button::id::SOUND_TAB:
                     {
                        gui.removeAllWidgets();
                        StateBase::Init();
                        tgui::Panel::Ptr cust(new Gui::SoundPanel(nullptr));
                        std::shared_ptr<Gui::SoundPanel> p = std::dynamic_pointer_cast<Gui::SoundPanel>(cust);
                        //p->init();
                        gui.add(cust);
                    }
                    break;
                    case Button::id::DEV_TAB:
                     {
                        gui.removeAllWidgets();
                        StateBase::Init();
                        tgui::Panel::Ptr cust(new Gui::DevPanel());
                        std::shared_ptr<Gui::DevPanel> p = std::dynamic_pointer_cast<Gui::DevPanel>(cust);
                        //p->init();
                        gui.add(cust);
                    }
                    break;
                    case Button::id::MULTIPLAYER:
                     {
                        gui.removeAllWidgets();
                        StateBase::Init();
                        tgui::Panel::Ptr cust(new MultiplayerPanel());
                        std::shared_ptr<MultiplayerPanel> p = std::dynamic_pointer_cast<MultiplayerPanel>(cust);
                        //p->init();
                        gui.add(cust);
                    }
                    break;
                    case Button::id::HOST:
                     {
                        gui.removeAllWidgets();
                        StateBase::Init();
                        tgui::Panel::Ptr cust(new HostPanel());
                        std::shared_ptr<HostPanel> p = std::dynamic_pointer_cast<HostPanel>(cust);
                        //p->init();
                        gui.add(cust);
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
