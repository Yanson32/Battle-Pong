#include "States/StateBase.h"
#include "Settings.h"
#include "Objects/Ball.h"
#include "Objects/Wall.h"
#include "Objects/Paddle.h"
#include "Input/AI.h"
#include <GameUtilities/Engin/Engin.h>
#include "Objects/Goal.h"
#include <array>
#include "Events/EventManager.h"
#include "Events/PlaySound.h"
#include "Events/PlayMusic.h"
#include "Events/PaddleCollision.h"
#include "ResourceManager.h"
#include "Events/ChangeState.h"

sf::RenderWindow StateBase::window(Settings::inst().getWindowSettings().getVideoMode(), Settings::inst().getTitle());
std::shared_ptr<b2World> StateBase::world(new b2World(b2Vec2(0, 0)));
tgui::Gui StateBase::gui(window);
DebugDraw StateBase::debugDraw(*world);
sf::Text StateBase::userMessage;
sf::Clock StateBase::messageClock;

namespace
{
    std::array<sf::Vector2f, 4> horizontalPoints = {sf::Vector2f(-400, -25), sf::Vector2f(400, -25), sf::Vector2f(400, 25), sf::Vector2f(-400, 25)};
    std::array<sf::Vector2f, 4> verticalPoints = {sf::Vector2f(-25, -300), sf::Vector2f(25, -300), sf::Vector2f(25, 300), sf::Vector2f(-25, 300)};
    std::array<sf::Vector2f, 4> paddlePoints = {sf::Vector2f(-10, -50), sf::Vector2f(10, -50), sf::Vector2f(10, 50),sf::Vector2f(-10, 50)};
    std::array<sf::Vector2f, 4> goalPoints = {sf::Vector2f(-15, -600), sf::Vector2f(15, -600), sf::Vector2f(15, 600), sf::Vector2f(-15, 600)};
}
std::unique_ptr<Wall> StateBase::ground(new Wall(world, horizontalPoints));
std::unique_ptr<Wall> StateBase::celing(new Wall(world, horizontalPoints));
std::unique_ptr<Wall> StateBase::leftWall(new Wall(world, verticalPoints));
std::unique_ptr<Wall> StateBase::RightWall(new Wall(world, verticalPoints));


std::unique_ptr<Paddle> StateBase::leftPaddle(new Paddle(world, ObjectId::LEFT_PADDLE, paddlePoints));
std::unique_ptr<Paddle> StateBase::rightPaddle(new Paddle(world, ObjectId::RIGHT_PADDLE, paddlePoints));

std::unique_ptr<Goal> StateBase::leftGoal(new Goal(world, ObjectId::LEFT_GOAL, goalPoints));
std::unique_ptr<Goal> StateBase::rightGoal(new Goal(world, ObjectId::RIGHT_GOAL, goalPoints));
std::unique_ptr<Ball> StateBase::ball(new Ball(world));

sf::Sound StateBase::sound;
sf::Music StateBase::music;

std::shared_ptr<PaddleHud> StateBase::paddle1Hud(new PaddleHud(Settings::inst().paddle1));
std::shared_ptr<PaddleHud> StateBase::paddle2Hud(new PaddleHud(Settings::inst().paddle2));

ContactListener StateBase::contactListener;
sf::Clock StateBase::roundClock;

StateBase::StateBase(Engin::Engin& newEngin, const stateId newState):
state(newState),
Engin::GameState(),
engin(newEngin),
sysPause(false)
{

    rightGoal->setPosition(sf::Vector2f(760, 300));
    leftPaddle->setColor(sf::Color(255, 100, 0));
    rightPaddle->setColor(sf::Color::Blue);



    leftPaddle->setInput(std::unique_ptr<AI>(new AI(*leftPaddle)));



    rightPaddle->setInput(std::unique_ptr<AI>(new AI(*rightPaddle)));

    ground->setPosition({400, 600});
    celing->setPosition({400, 0});
    leftWall->setPosition({0, 300});
    RightWall->setPosition({800, 300});

    world->SetDebugDraw(&debugDraw);

    debugDraw.SetFlags(b2Draw::e_aabbBit | b2Draw::e_jointBit | b2Draw::e_shapeBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);

    world->SetContactListener(&contactListener);

    paddle2Hud->setPosition({650, 0});
    gui.add(paddle1Hud);
    gui.add(paddle2Hud);

}

bool StateBase::isBallOnScreen()
{
    sf::Vector2f pos = ball->getPosition();
    auto size = window.getSize();
    sf::FloatRect windowBounds;
    windowBounds.top = 0;
    windowBounds.left = 0;
    windowBounds.width = size.x;
    windowBounds.height = size.y;

    return windowBounds.contains(pos);

}

void StateBase::Update(Engin::Engin& engin, const int &deltaTime)
{
    if(!IsPaused())
    {

        if(!isBallOnScreen())
        {
            reset();
        }
        if(roundClock.getElapsedTime().asSeconds() >= 30)
        {
            reset();
        }
    }
}


void StateBase::Draw(Engin::Engin& engin, const int &deltaTime)
{
    window.clear();
    window.draw(*leftPaddle);
    window.draw(*rightPaddle);

    window.draw(*celing);
    window.draw(*leftWall);
    window.draw(*RightWall);
    window.draw(*ground);
    window.draw(*paddle1Hud);
    window.draw(*paddle2Hud);
    gui.draw();

    #ifdef DEBUG
        window.draw(debugDraw);
    #endif
}

void StateBase::systemPause(const bool newSysPause)
{
    sysPause = newSysPause;
}

bool StateBase::isSystemPaused() const
{

    return sysPause;
}

void StateBase::reset()
{
    ball->setPosition({400, 300});
    ball->setVelocity({100, 100});
    leftPaddle->setPosition(sf::Vector2f(100, 300));
    rightPaddle->setPosition(sf::Vector2f(700, 300));
    rightPaddle->handleInput(*ball);
    userMessage.setString("Ready!");
    centerText();
    messageClock.restart();
    roundClock.restart();
    systemPause(true);
}

void StateBase::gameEvents()
{

        //GameUtilities event loop
        Evt::EventPtr evtPtr;
        while(EventManager::inst().Poll((evtPtr)))
        {
            //EventManager::inst().Dispatch((evtPtr));
            switch(evtPtr->id)
            {
                case EventId::LEFT_GOAL_COLLISION:
                {
                    int currentScore = Settings::inst().paddle1->getScore();
                    Settings::inst().paddle1->setScore(currentScore + 1);
                    paddle1Hud->setScore(currentScore + 1);
                    reset();
                }
                break;
                case EventId::RIGHT_GOAL_COLLISION:
                {
                    int currentScore = Settings::inst().paddle2->getScore();
                    Settings::inst().paddle2->setScore(currentScore + 1);
                    paddle2Hud->setScore(currentScore + 1);
                    reset();
                }
                break;
                case EventId::PLAY_MUSIC:
                {
                    std::shared_ptr<PlayMusic> temp =  std::dynamic_pointer_cast<PlayMusic>(evtPtr);
                    if(temp)
                    {
                        if(music.openFromFile(temp->file))
                        {
                            music.play();
                            //music.setVolume(254);
                        }
                        else
                        {
                            std::cout << "Unable to open music file " << std::endl;
                        }

                    }
                    else
                    {
                        std::cout << "Cast failes MusicListener::OnEvent" << std::endl;
                    }
                }
                break;
                case EventId::PLAY_SOUND:
                {
                    std::shared_ptr<PlaySound> temp =  std::dynamic_pointer_cast<PlaySound>(evtPtr);

                    if(temp && ResourceManager::sound.isLoaded(temp->soundId))
                    {
                        sound.setBuffer(ResourceManager::sound.get(temp->soundId));
                        sound.play();
                    }
                }
                break;
                case EventId::MUSIC_VOLUME_CHANGED:
                {
                    int volume = Settings::inst().musicSettings->getVolume();
                    music.setVolume(volume);
                }
                break;
                case EventId::SOUND_VOLUME_CHANGED:
                {
                    int volume = Settings::inst().musicSettings->getSoundVolume();
                    sound.setVolume(volume);
                    std::cout << "Sound Volume Changed " << volume << std::endl;
                }
                break;
                case BALL_COLLISION:
                    EventManager::inst().Post<PlaySound>("Ball Sound");
                break;
                case EventId::GOAL_COLLISION:
                {
                    //sound.setVolume(Settings::inst().musicSettings->getSoundVolume());
                }
                break;

                case PADDLE_COLLISION:
                {
                    std::shared_ptr<PaddleCollision> temp =  std::dynamic_pointer_cast<PaddleCollision>(evtPtr);

                    if(temp)
                    {
//                        static ObjectId currentPaddle = ObjectId::NONE;
//                        if(temp->paddle == currentPaddle)
//                            reset();
//                        else
//                            currentPaddle = temp->paddle;
                        //std::cout << "Paddle and ball collided id " << temp->paddle << std::endl;
                    }
                }
                break;
                case EventId::CHANGE_STATE:
                {
                    std::shared_ptr<ChangeState> temp =  std::dynamic_pointer_cast<ChangeState>(evtPtr);
                    switch(temp->state)
                    {
                        case stateId::CONNECT_STATE:
                            std::cout << "Connect state" << std::endl;
                        break;

                    }
                }
                break;

            }

        }

}

void StateBase::centerText()
{
    sf::FloatRect bounds = userMessage.getGlobalBounds();

    float originX = bounds.width / 2;
    float originY = bounds.height / 2;

    userMessage.setOrigin({originX, originY});

}

void StateBase::Init()
{
    systemPause(false);
    Pause(false);
    music.setVolume(Settings::inst().musicSettings->getVolume());
    sound.setVolume(Settings::inst().musicSettings->getSoundVolume());
}


void StateBase::sfEvent(Engin::Engin& engin, const sf::Event &event)
{
    switch (event.type)
    {

        case sf::Event::Closed:
            engin.Quit();
            break;
    }
}

void StateBase::guEvent(Engin::Engin& engin, Evt::EventPtr event)
{
    switch(event->id)
    {
        case EventId::LEFT_GOAL_COLLISION:
        {
            int currentScore = Settings::inst().paddle1->getScore();
            Settings::inst().paddle1->setScore(currentScore + 1);
            paddle1Hud->setScore(currentScore + 1);
            reset();
        }
        break;
        case EventId::RIGHT_GOAL_COLLISION:
        {
            int currentScore = Settings::inst().paddle2->getScore();
            Settings::inst().paddle2->setScore(currentScore + 1);
            paddle2Hud->setScore(currentScore + 1);
            reset();
        }
        break;
        case EventId::PLAY_SOUND:
        {
            std::shared_ptr<PlaySound> temp =  std::dynamic_pointer_cast<PlaySound>(event);

            if(temp && ResourceManager::sound.isLoaded(temp->soundId))
            {
                sound.setBuffer(ResourceManager::sound.get(temp->soundId));
                sound.play();
            }
        }
        break;
        case BALL_COLLISION:
            EventManager::inst().Post<PlaySound>("Ball Sound");
        break;
    }
}


StateBase::~StateBase()
{
}
