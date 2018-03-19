#include "States/OptionsState.h"
#include <GameUtilities/Engin/Engin.h>
#include "Objects/Paddle.h"
#include "Objects/Ball.h"
#include "Objects/Wall.h"
#include "States/IntroState.h"
#include "States/ControlState.h"
#include "Settings.h"
#include "Events/Events.h"
#include "States/MusicState.h"
#include "ResourceManager.h"
#include "Sounds/Id.h"

OptionsState::OptionsState(GU::Engin::Engin& newEngin): StateBase(newEngin, stateId::OPTIONS_STATE)
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

    saveButton = tgui::Button::create("Load");
    saveButton->connect("pressed", &OptionsState::onLoadPressed, this);
    saveButton->setPosition(Settings::inst().buttonPosition(2));
    saveButton->setSize(Settings::inst().buttonSize());

    loadButton = tgui::Button::create("Save");
    loadButton->connect("pressed", &OptionsState::onSavePressed, this);
    loadButton->setPosition(Settings::inst().buttonPosition(3));
    loadButton->setSize(Settings::inst().buttonSize());

    backButton = tgui::Button::create("Back");
    backButton->connect("pressed", &OptionsState::onBackPressed, this);
    backButton->setPosition(Settings::inst().buttonPosition(4));
    backButton->setSize(Settings::inst().buttonSize());

}



void OptionsState::HandleEvents(GU::Engin::Engin& engin, const int &deltaTime)
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

void OptionsState::Update(GU::Engin::Engin& engin, const int &deltaTime)
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

void OptionsState::Draw(GU::Engin::Engin& engin, const int &deltaTime)
{
    StateBase::Draw(engin, deltaTime);
    window.draw(*ball);
    window.display();
}

void OptionsState::onControlsPressed()
{
    EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
    EventManager::inst().Post<GU::Evt::PushState>(stateId::CONTROL_STATE);
}

void OptionsState::onBackPressed()
{
    EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
    EventManager::inst().Post<GU::Evt::Pop>();
}

void OptionsState::onMusicPressed()
{
    EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
    EventManager::inst().Post<GU::Evt::PushState>(stateId::MUSIC_STATE);
}

void OptionsState::Init()
{
    //StateBase::Init();
    gui.add(musicButton);
    gui.add(backButton);
    gui.add(controlsButton);
    gui.add(loadButton);
    gui.add(saveButton);

    ResourceManager::sound.load(Sound::Id::BUTTON, "../Resources/Sounds/tone1.ogg");
    ResourceManager::sound.load(Sound::Id::BALL, "../Resources/Sounds/tone1.ogg");
    ResourceManager::font.load("Header Font", "../Resources/Fonts/caviar-dreams/CaviarDreams.ttf");
}

void OptionsState::Clean()
{
    gui.removeAllWidgets();

    ResourceManager::sound.remove(Sound::Id::BUTTON);
    ResourceManager::sound.remove(Sound::Id::BALL);
    ResourceManager::font.remove("Header Font");
}

void OptionsState::onLoadPressed()
{

}

void OptionsState::onSavePressed()
{

}


OptionsState::~OptionsState()
{
    //dtor
}
