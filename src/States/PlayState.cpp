#include "States/PlayState.h"
#include "Ball.h"
#include <SFML/Window/Event.hpp>
#include "Game.h"
#include <Box2D/Box2D.h>
#include <iostream>
#include "Box2DFunctions.h"
#include <SFML/Graphics/CircleShape.hpp>

#include "Wall.h"
#include "Paddle.h"
#include "AI.h"
#include "PlayerInput.h"
PlayState::PlayState(Engin::Engin& newEngin): StateBase(newEngin)
{
    leftPaddle->setInput(std::unique_ptr<Input>(new PlayerInput(*leftPaddle)));

}

void PlayState::HandleEvents(Engin::Engin& engin)
{
    if(window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {

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

        leftPaddle->handleInput(*ball);
        rightPaddle->handleInput(*ball);
    }
}

void PlayState::Update(Engin::Engin& engin)
{
    if(!IsPaused())
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
}

void PlayState::Draw(Engin::Engin& engin)
{

    StateBase::Draw(engin);
    window.display();
}


PlayState::~PlayState()
{
    delete celing;
    delete ground;
    delete leftWall;
    delete RightWall;
}
