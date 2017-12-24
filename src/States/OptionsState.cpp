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
OptionsState::OptionsState(Engin::Engin& newEngin): StateBase(newEngin)
{
    //ctor


    tgui::Button::Ptr controlsButton = tgui::Button::create("Controls");
    controlsButton->connect("pressed", &OptionsState::onControlsPressed, this);
    controlsButton->setPosition(Settings::inst().buttonPosition(0));
    controlsButton->setSize(Settings::inst().buttonSize());
    gui.add(controlsButton);

    tgui::Button::Ptr musicButton = tgui::Button::create("Music");
    musicButton->connect("pressed", &OptionsState::onMusicPressed, this);
    musicButton->setPosition(Settings::inst().buttonPosition(1));
    musicButton->setSize(Settings::inst().buttonSize());
    gui.add(musicButton);

    tgui::Button::Ptr backButton = tgui::Button::create("Back");
    backButton->connect("pressed", &OptionsState::onBackPressed, this);
    backButton->setPosition(Settings::inst().buttonPosition(4));
    backButton->setSize(Settings::inst().buttonSize());
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
    EventManager::inst().Post<PlaySound>("Button Sound");
}

void OptionsState::onBackPressed()
{
    gui.removeAllWidgets();
    engin.ChangeState<IntroState>(engin);
    EventManager::inst().Post<PlaySound>("Button Sound");
}

void OptionsState::onMusicPressed()
{
    EventManager::inst().Post<PlaySound>("Button Sound");
}

OptionsState::~OptionsState()
{
    //dtor
}
