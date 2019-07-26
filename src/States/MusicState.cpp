#include "States/MusicState.h"

#include "Objects/Ball.h"
#include "Objects/Paddle.h"
#include "Objects/Wall.h"

#include "Events/EventManager.h"
#include "Settings.h"
#include "States/OptionsState.h"
#include "Events/Events.h"
#include "Settings.h"
#include "ResourceManager.h"
#include "Sounds/Id.h"

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

void MusicState::HandleEvents(GU::Engin::Engin& engin, const float &deltaTime)
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

void MusicState::Update(GU::Engin::Engin& engin, const float &deltaTime)
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

void MusicState::Draw(GU::Engin::Engin& engin, const float &deltaTime)
{
    StateBase::Draw(engin, deltaTime);
    window.draw(*ball);
    window.display();
}

void MusicState::onBackPressed()
{
    EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
    EventManager::inst().Post<GU::Evt::Pop>();
}

void MusicState::Init()
{
    StateBase::Init();
//    ResourceManager::sound.load(Sound::Id::BUTTON, "../Resources/Sounds/tone1.ogg");
//    ResourceManager::sound.load(Sound::Id::BALL, "../Resources/Sounds/tone1.ogg");
    gui.add(backButton);
    gui.add(Settings::inst().musicSettings);
}
void MusicState::Clean()
{
    ResourceManager::sound.remove(Sound::Id::BUTTON);
    ResourceManager::sound.remove(Sound::Id::BALL);
    gui.removeAllWidgets();
}

void MusicState::sfEvent(GU::Engin::Engin& engin, const sf::Event &event)
{

}

void MusicState::handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event)
{
    StateBase::handleGUEvent(engin, event);
}

MusicState::~MusicState()
{
    //dtor
}
