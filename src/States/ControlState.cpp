#include "States/ControlState.h"
#include <GameUtilities/Engin/Engin.h>
#include "Objects/Paddle.h"
#include "Objects/Ball.h"
#include "Objects/Wall.h"
#include "Settings.h"
#include "States/PaddleState.h"
#include "States/OptionsState.h"
#include "Events/EventManager.h"
#include "Events/PlaySound.h"


ControlState::ControlState(Engin::Engin& newEngin): StateBase(newEngin)
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

void ControlState::HandleEvents(Engin::Engin& newEngin, const int &deltaTime)
{
    if(window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {

            gui.handleEvent(event);
            switch (event.type)
            {

                case sf::Event::Closed:
					engin.Quit();
                    break;


                case sf::Event::KeyPressed:
                    break;

                default:
                    break;
            }
        }

        leftPaddle->handleInput(*ball);
        rightPaddle->handleInput(*ball);

    }

    gameEvents();
}

void ControlState::Update(Engin::Engin& engin, const int &deltaTime)
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

void ControlState::Draw(Engin::Engin& engin, const int &deltaTime)
{
	StateBase::Draw(engin, deltaTime);
    gui.draw();
    window.display();
}

void ControlState::onPaddle1()
{
    gui.removeAllWidgets();
    engin.Push<PaddleState>(engin, Settings::inst().paddle1);
    EventManager::inst().Post<PlaySound>("Button Sound");
}

void ControlState::onPaddle2()
{
    gui.removeAllWidgets();
    engin.Push<PaddleState>(engin, Settings::inst().paddle2);
    EventManager::inst().Post<PlaySound>("Button Sound");
}

void ControlState::onBack()
{
    engin.Pop();
    EventManager::inst().Post<PlaySound>("Button Sound");
}

void ControlState::Init()
{
    gui.add(paddle1);
    gui.add(paddle2);
    gui.add(backButton);
}

void ControlState::Clean()
{
    gui.removeAllWidgets();

}

ControlState::~ControlState()
{
    //dtor
}
