#include "States/PlayState.h"
#include "Ball.h"
#include <SFML/Window/Event.hpp>
#include "Game.h"
#include <Box2D/Box2D.h>
#include <iostream>
#include "Box2DFunctions.h"
#include <SFML/Graphics/CircleShape.hpp>

PlayState::PlayState(): ball(*world)
{
    std::array<sf::Vector2f, 4> horizontalPoints;
    horizontalPoints[0] = sf::Vector2f(-400, -25);
    horizontalPoints[1] = sf::Vector2f(400, -25);
    horizontalPoints[2] = sf::Vector2f(400, 25);
    horizontalPoints[3] = sf::Vector2f(-400, 25);

    std::array<sf::Vector2f, 4> verticalPoints;
    verticalPoints[0] = sf::Vector2f(-25, -300);
    verticalPoints[1] = sf::Vector2f(25, -300);
    verticalPoints[2] = sf::Vector2f(25, 300);
    verticalPoints[3] = sf::Vector2f(-25, 300);

    ground = new Wall(*world, horizontalPoints);
    celing = new Wall(*world, horizontalPoints);
    leftWall = new Wall(*world, verticalPoints);
    RightWall = new Wall(*world, verticalPoints);

    ground->setPosition(sf::Vector2f(400, 600));
    celing->setPosition(sf::Vector2f(400, 0));
    leftWall->setPosition(sf::Vector2f(0, 300));
    RightWall->setPosition(sf::Vector2f(800, 300));

    world->SetDebugDraw(&debugDraw);

    debugDraw.SetFlags(b2Draw::e_aabbBit | b2Draw::e_jointBit | b2Draw::e_shapeBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);

    //        e_shapeBit ( draw shapes )
//        e_jointBit ( draw joint connections
//        e_aabbBit ( draw axis aligned bounding boxes )
//        e_pairBit ( draw broad-phase pairs )
//        e_centerOfMassBit ( draw a marker at body CoM )
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
                    break;

                default:
                    break;
            }
        }
    }
}

void PlayState::Update(Engin::Engin& engin)
{
    if(!IsPaused())
    {
        world->Step( timeStep, velocityIterations, positionIterations);
        debugDraw.update();
        ball.update();
        ground->update();
        celing->update();
        leftWall->update();
        RightWall->update();

    }
}

void PlayState::Draw(Engin::Engin& engin)
{
    window.clear();
    //window.draw(debugDraw);
    window.draw(ball);
    window.draw(*celing);
    window.draw(*leftWall);
    window.draw(*RightWall);
    window.draw(*ground);
    window.display();
}


PlayState::~PlayState()
{
    delete celing;
    delete ground;
    delete leftWall;
    delete RightWall;
}
