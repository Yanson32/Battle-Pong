#include "States/OptionsState.h"
#include <GameUtilities/Engin/Engin.h>
#include "Objects/Paddle.h"
#include "Objects/Ball.h"
#include "Objects/Wall.h"
#include "States/IntroState.h"
#include "States/ControlState.h"
#include "Settings.h"
#include "Events/EventManager.h"
#include "Events/PlaySound.h"
#include "States/MusicState.h"
#include "ResourceManager.h"

OptionsState::OptionsState(Engin::Engin& newEngin): StateBase(newEngin, stateId::OPTIONS_STATE)
{
    //ctor
    controlsButton = tgui::Button::create("Controls");
    controlsButton->connect("pressed", &OptionsState::onControlsPressed, this);
    controlsButton->setPosition(Settings::inst().buttonPosition(0));
    controlsButton->setSize(Settings::inst().buttonSize());

    musicButton = tgui::Button::create("Music");
    musicButton->connect("pressed", &OptionsState::onMusicPressed, this);
    musicButton->setPosition(Settings::inst().buttonPosition(1));
    musicButton->setSize(Settings::inst().buttonSize());

    backButton = tgui::Button::create("Back");
    backButton->connect("pressed", &OptionsState::onBackPressed, this);
    backButton->setPosition(Settings::inst().buttonPosition(4));
    backButton->setSize(Settings::inst().buttonSize());

}



void OptionsState::HandleEvents(Engin::Engin& engin, const int &deltaTime)
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
    Evt::EventPtr evtPtr;
    while(EventManager::inst().Poll((evtPtr)))
    {
        StateBase::guEvent(engin, evtPtr);
        guEvent(engin, evtPtr);
    }
}

void OptionsState::Update(Engin::Engin& engin, const int &deltaTime)
{
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

void OptionsState::Draw(Engin::Engin& engin, const int &deltaTime)
{
    StateBase::Draw(engin, deltaTime);
    window.draw(*ball);
    window.display();
}

void OptionsState::onControlsPressed()
{
    engin.Push<ControlState>(engin);
    EventManager::inst().Post<PlaySound>("Button Sound");
}

void OptionsState::onBackPressed()
{
    engin.Pop();
    EventManager::inst().Post<PlaySound>("Button Sound");
}

void OptionsState::onMusicPressed()
{
    engin.Push<MusicState>(engin);
    EventManager::inst().Post<PlaySound>("Button Sound");
}

void OptionsState::Init()
{
    //StateBase::Init();
    gui.add(musicButton);
    gui.add(backButton);
    gui.add(controlsButton);

    ResourceManager::sound.load("Button Sound", "../Resources/Sounds/tone1.ogg");
    ResourceManager::sound.load("Ball Sound", "../Resources/Sounds/tone1.ogg");
    ResourceManager::font.load("Header Font", "../Resources/Fonts/caviar-dreams/CaviarDreams.ttf");
}

void OptionsState::Clean()
{
    gui.removeAllWidgets();

    ResourceManager::sound.remove("Button Sound");
    ResourceManager::sound.remove("Ball Sound");
    ResourceManager::font.remove("Header Font");
}

void OptionsState::sfEvent(Engin::Engin& engin, const sf::Event &event)
{

}

void OptionsState::guEvent(Engin::Engin& engin, Evt::EventPtr event)
{

}

OptionsState::~OptionsState()
{
    //dtor
}
