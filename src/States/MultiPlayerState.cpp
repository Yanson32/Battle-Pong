#include "States/MultiPlayerState.h"

#include "GameUtilities/Engin/Engin.h"
#include "Objects/Wall.h"
#include "Objects/Ball.h"
#include "Objects/Paddle.h"
#include <string>


MultiPlayerState::MultiPlayerState(Engin::Engin& engin,
const std::string ipAddress,
const std::string port,
const bool host
):PlayState::PlayState(engin)
{

}

/****************************************************************//**
*   @brief  This method handles input such as user input and events.
*           This should be called once per frame.
*   @param  engin A reference to an Engin::Engin object.
*           This is the main game object.
********************************************************************/
void MultiPlayerState::HandleEvents(Engin::Engin& engin, const int &deltaTime)
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


/****************************************************************//**
*   @brief  This method updates the game logic. This should be
*           called once per frame.
*   @param  engin A reference to an Engin::Engin object.
*           This is the main game object.
********************************************************************/
void MultiPlayerState::Update(Engin::Engin& engin, const int &deltaTime)
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
void MultiPlayerState::Draw(Engin::Engin& engin, const int &deltaTime)
{
	StateBase::Draw(engin, deltaTime);
	//window.draw(header);
	window.draw(*ball);
    window.display();
}

void MultiPlayerState::Init()
{

}
void MultiPlayerState::Clean()
{

}


MultiPlayerState::~MultiPlayerState()
{

}
