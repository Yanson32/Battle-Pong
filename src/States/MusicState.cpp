#include "States/MusicState.h"

#include "Objects/Ball.h"
#include "Objects/Paddle.h"
#include "Objects/Wall.h"

#include "Events/EventManager.h"
#include "Settings.h"
#include "States/OptionsState.h"
#include "Events/PlaySound.h"
#include "Events/EventManager.h"
#include "Settings.h"

MusicState::MusicState(Engin::Engin& engin): StateBase(engin)
{
    //ctor
    tgui::Button::Ptr backButton = tgui::Button::create("Back");
    backButton->connect("pressed", &MusicState::onBackPressed, this);
    backButton->setPosition(Settings::inst().buttonPosition(4));
    backButton->setSize(Settings::inst().buttonSize());
    gui.add(backButton);

    //Settings::inst().musicSettings.setPosition({300, 300});
    gui.add(Settings::inst().musicSettings);
}

void MusicState::HandleEvents(Engin::Engin& engin)
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

    gameEvents();
}

void MusicState::Update(Engin::Engin& engin)
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

void MusicState::Draw(Engin::Engin& engin)
{
    StateBase::Draw(engin);
    gui.draw();
    window.display();
}

void MusicState::onBackPressed()
{
    gui.removeAllWidgets();
    engin.ChangeState<OptionsState>(engin);
    EventManager::inst().Post<PlaySound>("Button Sound");
}

MusicState::~MusicState()
{
    //dtor
}
