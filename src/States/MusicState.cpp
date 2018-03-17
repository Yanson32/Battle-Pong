#include "States/MusicState.h"

#include "Objects/Ball.h"
#include "Objects/Paddle.h"
#include "Objects/Wall.h"

#include "Events/EventManager.h"
#include "Settings.h"
#include "States/OptionsState.h"
#include "Events/PlaySound.h"
#include "Events/EventManager.h"
#include "Settings.h"
#include "ResourceManager.h"

MusicState::MusicState(GU::Engin::Engin& engin): StateBase(engin, stateId::MUSIC_STATE)
{
    //ctor
    backButton = tgui::Button::create("Back");
    backButton->connect("pressed", &MusicState::onBackPressed, this);
    backButton->setPosition(Settings::inst().buttonPosition(4));
    backButton->setSize(Settings::inst().buttonSize());
    gui.add(backButton);

    //Settings::inst().musicSettings.setPosition({300, 300});
    gui.add(Settings::inst().musicSettings);
}

void MusicState::HandleEvents(GU::Engin::Engin& engin, const int &deltaTime)
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
        StateBase::guEvent(engin, evtPtr);
        guEvent(engin, evtPtr);
    }
}

void MusicState::Update(GU::Engin::Engin& engin, const int &deltaTime)
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

void MusicState::Draw(GU::Engin::Engin& engin, const int &deltaTime)
{
    StateBase::Draw(engin, deltaTime);
    window.draw(*ball);
    window.display();
}

void MusicState::onBackPressed()
{
    engin.Pop();
    EventManager::inst().Post<PlaySound>("Button Sound");
}

void MusicState::Init()
{
    StateBase::Init();
    ResourceManager::sound.load("Button Sound", "../Resources/Sounds/tone1.ogg");
    ResourceManager::sound.load("Ball Sound", "../Resources/Sounds/tone1.ogg");
    gui.add(backButton);
    gui.add(Settings::inst().musicSettings);
}
void MusicState::Clean()
{
    ResourceManager::sound.remove("Button Sound");
    ResourceManager::sound.remove("Ball Sound");
    gui.removeAllWidgets();
}

void MusicState::sfEvent(GU::Engin::Engin& engin, const sf::Event &event)
{

}

void MusicState::guEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event)
{

}

MusicState::~MusicState()
{
    //dtor
}
