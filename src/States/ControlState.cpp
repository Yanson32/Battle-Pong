
#include "States/ControlState.h"
#include <GameUtilities/Engin/Engin.h>
#include "Objects/Paddle.h"
#include "Objects/Ball.h"
#include "Objects/Wall.h"
#include "Settings.h"
#include "States/PaddleState.h"
#include "States/OptionsState.h"
#include "States/Id.h"
#include "Events/Events.h"
#include "ResourceManager.h"
#include "Sounds/Id.h"

ControlState::ControlState(GU::Engin::Engin& newEngin): StateBase(newEngin, stateId::CONTROL_STATE)
{
    //ctor
    paddle1 = tgui::Button::create("Paddle 1");
    paddle1->setPosition(Settings::inst().buttonPosition(0));
    paddle1->setSize(Settings::inst().buttonSize());
    paddle1->connect("pressed", &ControlState::onPaddle1, this);


    paddle2 = tgui::Button::create("Paddle 2");
    paddle2->setSize(Settings::inst().buttonSize());
    paddle2->setPosition(Settings::inst().buttonPosition(1));
    paddle2->connect("pressed", &ControlState::onPaddle2, this);


    backButton = tgui::Button::create("Back");
    backButton->setSize(Settings::inst().buttonSize());
    backButton->setPosition(Settings::inst().buttonPosition(4));
    backButton->connect("pressed", &ControlState::onBack, this);

}

void ControlState::HandleEvents(GU::Engin::Engin& newEngin, const float &deltaTime)
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

void ControlState::Update(GU::Engin::Engin& engin, const float &deltaTime)
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

void ControlState::Draw(GU::Engin::Engin& engin, const float &deltaTime)
{
	window.draw(*ball);
	StateBase::Draw(engin, deltaTime);
    window.display();
}

void ControlState::onPaddle1()
{
    gui.removeAllWidgets();
    engin.Push<PaddleState>(engin, Settings::inst().paddle1);
    EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
    EventManager::inst().Post<GU::Evt::PushState>(stateId::PADDLE_ONE_STATE);
}

void ControlState::onPaddle2()
{
    EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
    EventManager::inst().Post<GU::Evt::PushState>(stateId::PADDLE_TWO_STATE);
}

void ControlState::onBack()
{
    std::cout << "ControlState::onBack" << std::endl;
    EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
    EventManager::inst().Post<GU::Evt::Pop>();
}

void ControlState::Init()
{
    StateBase::Init();
    ResourceManager::sound.load(Sound::Id::BUTTON, "../Resources/Sounds/tone1.ogg");
    ResourceManager::sound.load(Sound::Id::BALL, "../Resources/Sounds/tone1.ogg");
    gui.add(paddle1);
    gui.add(paddle2);
    gui.add(backButton);
}

void ControlState::Clean()
{
    gui.removeAllWidgets();
    ResourceManager::sound.remove(Sound::Id::BUTTON);
    ResourceManager::sound.remove(Sound::Id::BALL);

}

ControlState::~ControlState()
{
    //dtor
}
