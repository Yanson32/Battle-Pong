#include "States/StateBase.h"
#include "Settings.h"
#include "Objects/Ball.h"
#include "Objects/Wall.h"
#include "Objects/Paddle.h"
#include "Input/AI.h"
#include <GameUtilities/Engin/Engin.h>
#include "Objects/Goal.h"
#include <array>
#include "ResourceManager.h"
#include "States/States.h"
#include "Events/Events.h"
#include "Sounds/Id.h"

sf::RenderWindow StateBase::window;
std::shared_ptr<b2World> StateBase::world(new b2World(b2Vec2(0, 0)));
tgui::Gui StateBase::gui(window);
DebugDraw StateBase::debugDraw(*world);
sf::Text StateBase::userMessage;
sf::Clock StateBase::messageClock;

std::unique_ptr<Wall> StateBase::ground;
std::unique_ptr<Wall> StateBase::celing;
std::unique_ptr<Wall> StateBase::leftWall;
std::unique_ptr<Wall> StateBase::RightWall;


std::unique_ptr<Paddle> StateBase::leftPaddle;
std::unique_ptr<Paddle> StateBase::rightPaddle;

std::unique_ptr<Goal> StateBase::leftGoal;
std::unique_ptr<Goal> StateBase::rightGoal;
std::unique_ptr<Ball> StateBase::ball;

sf::Sound StateBase::sound;
sf::Music StateBase::music;

std::shared_ptr<PaddleHud> StateBase::paddle1Hud(new PaddleHud(tempSettings::paddle1));
std::shared_ptr<PaddleHud> StateBase::paddle2Hud(new PaddleHud(tempSettings::paddle2));

ContactListener StateBase::contactListener;
sf::Clock StateBase::roundClock;

StateBase::StateBase(GU::Engin::Engin& newEngin, const stateId newState):
state(newState),
GU::Engin::GameState(),
engin(newEngin),
sysPause(false)
{
    float &width = tempSettings::wDimensions.x;
    float &height = tempSettings::wDimensions.y;

    StateBase::window.create(sf::VideoMode(width, height), Settings::inst().getTitle());
    std::array<sf::Vector2f, 4> horizontalPoints = {sf::Vector2f(-width, -25), sf::Vector2f(width, -25), sf::Vector2f(width, 25), sf::Vector2f(-width, 25)};
    std::array<sf::Vector2f, 4> verticalPoints = {sf::Vector2f(-25, -height), sf::Vector2f(25, -height), sf::Vector2f(25, height), sf::Vector2f(-25, height)};
    std::array<sf::Vector2f, 4> paddlePoints = {sf::Vector2f(-10, -50), sf::Vector2f(10, -50), sf::Vector2f(10, 50),sf::Vector2f(-10, 50)};
    std::array<sf::Vector2f, 4> goalPoints = {sf::Vector2f(-15, -height), sf::Vector2f(15, -height), sf::Vector2f(15, height), sf::Vector2f(-15, height)};

    ground.reset(new Wall(world, horizontalPoints));
    celing.reset(new Wall(world, horizontalPoints));
    leftWall.reset(new Wall(world, verticalPoints));
    RightWall.reset(new Wall(world, verticalPoints));
    leftPaddle.reset(new Paddle(world, ObjectId::LEFT_PADDLE, paddlePoints));
    rightPaddle.reset(new Paddle(world, ObjectId::RIGHT_PADDLE, paddlePoints));

    leftGoal.reset(new Goal(world, ObjectId::RIGHT_GOAL, goalPoints));
    rightGoal.reset(new Goal(world, ObjectId::LEFT_GOAL, goalPoints));
    ball.reset(new Ball(world));
	
    rightGoal->setPosition(sf::Vector2f(760, 300));
    leftPaddle->setColor(sf::Color(255, 100, 0));
    rightPaddle->setColor(sf::Color::Blue);



    leftPaddle->setInput(std::unique_ptr<AI>(new AI(*leftPaddle)));



    rightPaddle->setInput(std::unique_ptr<AI>(new AI(*rightPaddle)));

    ground->setPosition({400, 525});
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

void StateBase::Update(GU::Engin::Engin& engin, const float &deltaTime)
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


void StateBase::Draw(GU::Engin::Engin& engin, const float &deltaTime)
{
    window.clear();
    window.draw(*leftPaddle);
    window.draw(*rightPaddle);

    window.draw(*celing);
    window.draw(*leftWall);
    window.draw(*RightWall);
    window.draw(*ground);

    #ifdef DEBUG
        window.draw(debugDraw);
    #endif

    gui.draw();
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

//        //GameUtilities event loop
//        GU::Evt::EventPtr evtPtr;
//        while(EventManager::inst().Poll((evtPtr)))
//        {
//            //EventManager::inst().Dispatch((evtPtr));
//            switch(evtPtr->id)
//            {
//                case EventId::LEFT_GOAL_COLLISION:
//                {
//                    int currentScore = Settings::inst().paddle1->getScore();
//                    Settings::inst().paddle1->setScore(currentScore + 1);
//                    paddle1Hud->setScore(currentScore + 1);
//                    reset();
//                }
//                break;
//                case EventId::RIGHT_GOAL_COLLISION:
//                {
//                    int currentScore = Settings::inst().paddle2->getScore();
//                    Settings::inst().paddle2->setScore(currentScore + 1);
//                    paddle2Hud->setScore(currentScore + 1);
//                    reset();
//                }
//                break;
//                case EventId::PLAY_MUSIC:
//                {
//                    std::shared_ptr<PlayMusic> temp =  std::dynamic_pointer_cast<PlayMusic>(evtPtr);
//                    if(temp)
//                    {
//                        if(music.openFromFile(temp->file))
//                        {
//                            music.play();
//                            //music.setVolume(254);
//                        }
//                        else
//                        {
//                            std::cout << "Unable to open music file " << std::endl;
//                        }
//
//                    }
//                    else
//                    {
//                        std::cout << "Cast failes MusicListener::OnEvent" << std::endl;
//                    }
//                }
//                break;
//                case EventId::PLAY_SOUND:
//                {
//                    std::cout << "Play Sound" << std::endl;
//                    std::shared_ptr<PlaySound> temp =  std::dynamic_pointer_cast<PlaySound>(evtPtr);
//
//                    if(temp && ResourceManager::sound.isLoaded(temp->soundId))
//                    {
//                        sound.setBuffer(ResourceManager::sound.get(temp->soundId));
//                        sound.play();
//                    }
//                }
//                break;
//                case EventId::MUSIC_VOLUME_CHANGED:
//                {
//                    int volume = Settings::inst().musicSettings->getVolume();
//                    music.setVolume(volume);
//                }
//                break;
//                case EventId::SOUND_VOLUME_CHANGED:
//                {
//                    int volume = Settings::inst().musicSettings->getSoundVolume();
//                    sound.setVolume(volume);
//                    std::cout << "Sound Volume Changed " << volume << std::endl;
//                }
//                break;
//                case BALL_COLLISION:
//                    EventManager::inst().Post<PlaySound>("Ball Sound");
//                break;
//                case EventId::GOAL_COLLISION:
//                {
//                    //sound.setVolume(Settings::inst().musicSettings->getSoundVolume());
//                }
//                break;
//
//                case PADDLE_COLLISION:
//                {
//                    std::shared_ptr<PaddleCollision> temp =  std::dynamic_pointer_cast<PaddleCollision>(evtPtr);
//
//                    if(temp)
//                    {
////                        static ObjectId currentPaddle = ObjectId::NONE;
////                        if(temp->paddle == currentPaddle)
////                            reset();
////                        else
////                            currentPaddle = temp->paddle;
//                        //std::cout << "Paddle and ball collided id " << temp->paddle << std::endl;
//                    }
//                }
//                break;
//                case EventId::CHANGE_STATE:
//                {
//                    std::shared_ptr<ChangeState> temp =  std::dynamic_pointer_cast<ChangeState>(evtPtr);
//                    switch(temp->state)
//                    {
//                        case stateId::CONNECT_STATE:
//                            std::cout << "Connect state" << std::endl;
//                        break;
//
//                    }
//                }
//                break;
//
//            }
//
//        }

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
    music.setVolume(tempSettings::music.mVolume);
    sound.setVolume(tempSettings::music.sVolume);
}


void StateBase::sfEvent(GU::Engin::Engin& engin, const sf::Event &event)
{
    switch (event.type)
    {

        case sf::Event::Closed:
            engin.Quit();
            break;
    }
}

void StateBase::handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event)
{
    switch(event->id)
    {
        case EventId::LEFT_GOAL_COLLISION:
        {
            int currentScore = tempSettings::paddle1.score;
	    tempSettings::paddle1.score = currentScore + 1;
            paddle1Hud->setScore(currentScore + 1);
            reset();
        }
        break;
        case EventId::RIGHT_GOAL_COLLISION:
        {
            int currentScore = tempSettings::paddle2.score;
	    tempSettings::paddle2.score = currentScore + 1;
            paddle2Hud->setScore(currentScore + 1);
            reset();
        }
        break;
        case EventId::PLAY_SOUND:
        {
            std::shared_ptr<GU::Evt::PlaySound> temp =  std::dynamic_pointer_cast<GU::Evt::PlaySound>(event);

            if(temp && ResourceManager::sound.isLoaded(temp->soundId))
            {
                sound.setBuffer(ResourceManager::sound.get(temp->soundId));
                sound.play();
            }
        }
        break;
        case EventId::BALL_COLLISION:
            EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BALL);
        break;
        case EventId::PUSH_STATE:
        {
            std::shared_ptr<GU::Evt::PushState> temp =  std::dynamic_pointer_cast<GU::Evt::PushState>(event);
            if(temp)
            {
                switch(temp->id)
                {
                    case stateId::PLAY_STATE:
                        engin.Push<PlayState>(engin);
                    break;
                    case stateId::OPTIONS_STATE:
                        //engin.Push<OptionsState>(engin);
                    break;
                    case stateId::MULTIPLAYER_CONTROL_STATE:
                        //engin.Push<MultiplayerControlState>(engin);
                    break;
                    case stateId::CLIENT_PLAY_STATE:
                        engin.Push<ClientPlayState>(engin);
                    break;
                    case stateId::CONNECT_STATE:
                        //engin.Push<ConnectState>(engin);
                    break;
                    case stateId::CONTROL_STATE:
                        //engin.Push<ControlState>(engin);
                    break;
//                    case stateId::DEMO_STATE:
//                        engin.Push<DemoState>(engin);
//                    break;
                    case stateId::HOST_PLAY_STATE:
                        engin.Push<HostPlayState>(engin);
                    break;
                    case stateId::HOST_STATE:
                        engin.Push<HostState>(engin);
                    break;
                    case stateId::INTRO_STATE:
                        engin.Push<IntroState>(engin);
                    break;
                    case stateId::MUSIC_STATE:
                        //engin.Push<MusicState>(engin);
                    break;
//                    case stateId::PADDLE_STATE:
//                        engin.Push<PaddleState>(engin);
//                    break;
                }
            }

        break;
        }
        case EventId::POP_STATE:
            engin.Pop();
        break;
        case EventId::CHANGE_STATE:
        {
            std::shared_ptr<GU::Evt::ChangeState> temp =  std::dynamic_pointer_cast<GU::Evt::ChangeState>(event);
            if(temp)
            {
                switch(temp->stateId)
                {
                    case stateId::HOST_PLAY_STATE:
                        engin.ChangeState<HostPlayState>(engin);
                    break;
                    case stateId::CONNECT_STATE:
                        engin.ChangeState<ClientPlayState>(engin);
                    break;
                }
            }
        }
        break;
    }
}


StateBase::~StateBase()
{
}
