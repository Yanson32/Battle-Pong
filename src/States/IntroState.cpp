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
#include "States/MultiplayerControlsState.h"
#include "Settings.h"

#include "Objects/Wall.h"
#include "Objects/Ball.h"
#include "Objects/Paddle.h"
#include "States/OptionsState.h"
#include "States/Id.h"
#include "Events/EventManager.h"
#include "GameUtilities/Event/PlaySound.h"


#include "ResourceManager.h"
#include "Logging.h"

IntroState::IntroState(GU::Engin::Engin& newEngin): StateBase(newEngin, stateId::INTRO_STATE)
{

    //ctor
    ball->setPosition({400, 300});
    ball->setVelocity({100, 100});
    leftPaddle->setPosition(sf::Vector2f(100, 300));
    rightPaddle->setPosition(sf::Vector2f(700, 300));

    header.setString(Settings::inst().getTitle());
    header.setCharacterSize(54);
    header.setColor(sf::Color::White);
    header.setPosition(sf::Vector2f(335, 25));
    header.setStyle(sf::Text::Bold);


    startButton = tgui::Button::create("Start");
    startButton->connect("pressed", &IntroState::onStartPressed, this);
    startButton->setPosition(Settings::inst().buttonPosition(0));
    startButton->setSize(Settings::inst().buttonSize());

    multiplayerButton = tgui::Button::create("Multiplayer");
    multiplayerButton->connect("pressed", &IntroState::onMultiplayerPressed, this);
    multiplayerButton->setPosition(Settings::inst().buttonPosition(1));
    multiplayerButton->setSize(Settings::inst().buttonSize());

    optionButton = tgui::Button::create("Options");
    optionButton->connect("pressed", &IntroState::onOptionsPressed, this);
    optionButton->setPosition(Settings::inst().buttonPosition(2));
    optionButton->setSize(Settings::inst().buttonSize());

}


void IntroState::HandleEvents(GU::Engin::Engin& engin, const int &deltaTime)
{
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

void IntroState::Update(GU::Engin::Engin& engin, const int &deltaTime)
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

void IntroState::Draw(GU::Engin::Engin& engin, const int &deltaTime)
{
	StateBase::Draw(engin, deltaTime);
	window.draw(header);
	window.draw(*ball);
    window.display();
}


void IntroState::onStartPressed()
{
    EventManager::inst().Post<GU::Evt::PlaySound>("Button Sound");
    EventManager::inst().Post<GU::Evt::PushState>(stateId::PLAY_STATE);
}

void IntroState::onOptionsPressed()
{
    EventManager::inst().Post<GU::Evt::PlaySound>("Button Sound");
    engin.Push<OptionsState>(engin);
}

void IntroState::Init()
{
    StateBase::Init();

    gui.add(startButton);
    gui.add(optionButton);
    gui.add(multiplayerButton);

    ResourceManager::sound.load("Message Sound", "../Resources/Sounds/tone1.ogg");
    ResourceManager::sound.load("Button Sound", "../Resources/Sounds/tone1.ogg");
    ResourceManager::sound.load("Ball Sound", "../Resources/Sounds/tone1.ogg");
    ResourceManager::font.load("Header Font", "../Resources/Fonts/caviar-dreams/CaviarDreams.ttf");

    header.setFont(ResourceManager::font.get("Header Font"));
}

void IntroState::Clean()
{
    gui.removeAllWidgets();

    ResourceManager::sound.remove("Message Sound");
    ResourceManager::sound.remove("Button Sound");
    ResourceManager::sound.remove("Ball Sound");
    ResourceManager::font.remove("Header Font");

}

void IntroState::onMultiplayerPressed()
{
    EventManager::inst().Post<GU::Evt::PlaySound>("Button Sound");
    engin.Push<MultiplayerControlState>(engin);
}



IntroState::~IntroState()
{
    //dtor


}
