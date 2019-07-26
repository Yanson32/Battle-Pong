#include "States/MultiplayerControlsState.h"
#include "States/HostState.h"
#include "States/ConnectState.h"

#include "GameUtilities/Engin/Engin.h"
#include <GameUtilities/Event/Event.h>
#include <GameUtilities/Event/EventQueue.h>

#include "Settings.h"

#include "Objects/Wall.h"
#include "Objects/Ball.h"
#include "Objects/Paddle.h"

#include "Events/Events.h"
#include "ResourceManager.h"
#include "Sounds/Id.h"






MultiplayerControlState::MultiplayerControlState(GU::Engin::Engin& engin): StateBase(engin, stateId::MULTIPLAYER_CONTROL_STATE)
{
    //ctor
    backButton = tgui::Button::create("Back");
    backButton->connect("pressed", &MultiplayerControlState::onBackPressed, this);
    backButton->setPosition(Settings::inst().buttonPosition(4));
    backButton->setSize(Settings::inst().buttonSize());

    hostButton = tgui::Button::create("Host");
    hostButton->connect("pressed", &MultiplayerControlState::onHostPressed, this);
    hostButton->setPosition(Settings::inst().buttonPosition(0));
    hostButton->setSize(Settings::inst().buttonSize());

    connectButton = tgui::Button::create("Connect");
    connectButton->connect("pressed", &MultiplayerControlState::onConnectPressed, this);
    connectButton->setPosition(Settings::inst().buttonPosition(1));
    connectButton->setSize(Settings::inst().buttonSize());

}

void MultiplayerControlState::Init()
{
    StateBase::Init();
//    ResourceManager::sound.load(Sound::Id::BUTTON, "../Resources/Sounds/tone1.ogg");
//    ResourceManager::sound.load(Sound::Id::BALL, "../Resources/Sounds/tone1.ogg");

    gui.add(backButton);
    gui.add(hostButton);
    gui.add(connectButton);
}
void MultiplayerControlState::Clean()
{
    ResourceManager::sound.remove(Sound::Id::BUTTON);
    ResourceManager::sound.remove(Sound::Id::BALL);
    gui.removeAllWidgets();
}

void MultiplayerControlState::onHostPressed()
{
    EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
    engin.Push<HostState>(engin);
}

void MultiplayerControlState::onConnectPressed()
{
    EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
    engin.Push<ConnectState>(engin);
}
/****************************************************************//**
*   @brief  This method handles input such as user input and events.
*           This should be called once per frame.
*   @param  engin A reference to an Engin::Engin object.
*           This is the main game object.
********************************************************************/
void MultiplayerControlState::HandleEvents(GU::Engin::Engin& newEngin, const float &deltaTime)
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

/****************************************************************//**
*   @brief  This method updates the game logic. This should be
*           called once per frame.
*   @param  engin A reference to an Engin::Engin object.
*           This is the main game object.
********************************************************************/
void MultiplayerControlState::Update(GU::Engin::Engin& engin, const float &deltaTime)
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


/****************************************************************//**
*   @brief  This method draws the current frame. This should be
*           called once per frame.
*   @param  engin A reference to an Engin::Engin object.
*           This is the main game object.
********************************************************************/
void MultiplayerControlState::Draw(GU::Engin::Engin& engin, const float &deltaTime)
{
	StateBase::Draw(engin, deltaTime);
    window.display();
}

void MultiplayerControlState::onBackPressed()
{
    EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
    EventManager::inst().Post<GU::Evt::Pop>();
}

void MultiplayerControlState::sfEvent(GU::Engin::Engin& engin, const sf::Event &event)
{

}

void MultiplayerControlState::guEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event)
{

}

MultiplayerControlState::~MultiplayerControlState()
{
    //dtor
}
