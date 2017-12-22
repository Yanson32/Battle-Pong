#include "States/OptionsState.h"
#include <GameUtilities/Engin/Engin.h>
#include "Paddle.h"
#include "Ball.h"
#include "Wall.h"
#include "States/IntroState.h"
#include "States/ControlState.h"

OptionsState::OptionsState(Engin::Engin& newEngin): StateBase(newEngin)
{
    //ctor


    tgui::Button::Ptr controlsButton = tgui::Button::create("Controls");
    controlsButton->connect("pressed", &OptionsState::onControlsPressed, this);
    controlsButton->setPosition({300, 300});
    controlsButton->setSize(200, 25);
    gui.add(controlsButton);

    tgui::Button::Ptr backButton = tgui::Button::create("Back");
    backButton->connect("pressed", &OptionsState::onBackPressed, this);
    backButton->setPosition({300, 350});
    backButton->setSize(200, 25);
    gui.add(backButton);
}



void OptionsState::HandleEvents(Engin::Engin& engin)
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

        leftPaddle->handleInput(*ball);
        rightPaddle->handleInput(*ball);
    }
}

void OptionsState::Update(Engin::Engin& engin)
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

void OptionsState::Draw(Engin::Engin& engin)
{
    StateBase::Draw(engin);
    gui.draw();
    window.display();
}

void OptionsState::onControlsPressed()
{
    gui.removeAllWidgets();
    engin.ChangeState<ControlState>(engin);
}

void OptionsState::onBackPressed()
{
    gui.removeAllWidgets();
    engin.ChangeState<IntroState>(engin);
}

OptionsState::~OptionsState()
{
    //dtor
}
