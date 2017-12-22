#include "States/ControlState.h"
#include <GameUtilities/Engin/Engin.h>
#include "Paddle.h"
#include "Ball.h"
#include "Wall.h"

ControlState::ControlState(Engin::Engin& newEngin): StateBase(newEngin)
{
    //ctor
}

void ControlState::HandleEvents(Engin::Engin& newEngin)
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
}

void ControlState::Update(Engin::Engin& engin)
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

void ControlState::Draw(Engin::Engin& engin)
{
	StateBase::Draw(engin);
    gui.draw();
    window.display();
}

ControlState::~ControlState()
{
    //dtor
}
