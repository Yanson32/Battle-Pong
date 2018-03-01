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
#include "ResourceManager.h"

MusicState::MusicState(Engin::Engin& engin): StateBase(engin, stateId::MUSIC_STATE)
{
    //ctor
    backButton = tgui::Button::create("Back");
    backButton->connect("pressed", &MusicState::onBackPressed, this);
    backButton->setPosition(Settings::inst().buttonPosition(4));
    backButton->setSize(Settings::inst().buttonSize());
    gui.add(backButton);

    //Settings::inst().musicSettings.setPosition({300, 300});
    gui.add(Settings::inst().musicSettings);
}

void MusicState::HandleEvents(Engin::Engin& engin, const int &deltaTime)
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

void MusicState::Update(Engin::Engin& engin, const int &deltaTime)
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

void MusicState::Draw(Engin::Engin& engin, const int &deltaTime)
{
    StateBase::Draw(engin, deltaTime);
    window.draw(*ball);
    window.display();
}

void MusicState::onBackPressed()
{
    engin.Pop();
    EventManager::inst().Post<PlaySound>("Button Sound");
}

void MusicState::Init()
{
    StateBase::Init();
    ResourceManager::sound.load("Button Sound", "../Resources/Sounds/tone1.ogg");
    ResourceManager::sound.load("Ball Sound", "../Resources/Sounds/tone1.ogg");
    gui.add(backButton);
    gui.add(Settings::inst().musicSettings);
}
void MusicState::Clean()
{
    ResourceManager::sound.remove("Button Sound");
    ResourceManager::sound.remove("Ball Sound");
    gui.removeAllWidgets();
}

MusicState::~MusicState()
{
    //dtor
}
