#include "States/PaddleState.h"
#include <GameUtilities/Engin/Engin.h>
#include "Paddle.h"
#include "Wall.h"
#include "Ball.h"
#include "States/ControlState.h"
#include "Events/EventManager.h"
#include "Events/PlaySound.h"

PaddleState::PaddleState(Engin::Engin& newEngin, tgui::Panel::Ptr newPSettings): StateBase(newEngin), pSettings(newPSettings)
{
    //ctor
    gui.add(pSettings);

    auto backButton = tgui::Button::create("Back");
    backButton->setSize(Settings::inst().buttonSize());
    backButton->setPosition(Settings::inst().buttonPosition(4));
    backButton->connect("pressed", &PaddleState::onBack, this);
    gui.add(backButton);

}


void PaddleState::HandleEvents(Engin::Engin& newEngin)
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
                    if(event.key.code == sf::Keyboard::P)
                    {
                        Pause(!IsPaused());
                    }
                    break;

                default:
                    break;
            }
        }

        //GameUtilities event loop
        Evt::EventPtr evtPtr;
        while(EventManager::inst().Poll((evtPtr)))
        {
            EventManager::inst().Dispatch((evtPtr));
        }

        leftPaddle->handleInput(*ball);
        rightPaddle->handleInput(*ball);
    }
}

void PaddleState::Update(Engin::Engin& engin)
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

void PaddleState::Draw(Engin::Engin& engin)
{
    StateBase::Draw(engin);
    gui.draw();
    window.display();
}

void PaddleState::onBack()
{
    gui.removeAllWidgets();
    engin.ChangeState<ControlState>(engin);
    EventManager::inst().Post<PlaySound>("Button Sound");
}

PaddleState::~PaddleState()
{
    //dtor
}
