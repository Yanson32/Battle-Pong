#include "States/OptionsState.h"
#include <GameUtilities/Engin/Engin.h>
#include "Objects/Paddle.h"
#include "Objects/Ball.h"
#include "Objects/Wall.h"
#include "States/IntroState.h"
#include "States/ControlState.h"
#include "Settings.h"
#include "Events/EventManager.h"
#include "Events/PlaySound.h"
#include "States/MusicState.h"

OptionsState::OptionsState(Engin::Engin& newEngin): StateBase(newEngin)
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

    backButton = tgui::Button::create("Back");
    backButton->connect("pressed", &OptionsState::onBackPressed, this);
    backButton->setPosition(Settings::inst().buttonPosition(4));
    backButton->setSize(Settings::inst().buttonSize());

}



void OptionsState::HandleEvents(Engin::Engin& engin, const int &deltaTime)
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

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            engin.Pop();
        }
    }

    gameEvents();
}

void OptionsState::Update(Engin::Engin& engin, const int &deltaTime)
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

void OptionsState::Draw(Engin::Engin& engin, const int &deltaTime)
{
    StateBase::Draw(engin, deltaTime);
    gui.draw();
    window.display();
}

void OptionsState::onControlsPressed()
{
    engin.Push<ControlState>(engin);
    EventManager::inst().Post<PlaySound>("Button Sound");
}

void OptionsState::onBackPressed()
{
    engin.Pop();
    EventManager::inst().Post<PlaySound>("Button Sound");
}

void OptionsState::onMusicPressed()
{
    engin.Push<MusicState>(engin);
    EventManager::inst().Post<PlaySound>("Button Sound");
}

void OptionsState::Init()
{


    gui.add(musicButton);
    gui.add(backButton);
    gui.add(controlsButton);
}

void OptionsState::Clean()
{
    gui.removeAllWidgets();
}

OptionsState::~OptionsState()
{
    //dtor
}
