#include "States/StateBase.h"
#include "Settings.h"
#include "Objects/Ball.h"
#include "Objects/Wall.h"
#include "Objects/Paddle.h"
#include "Input/AI.h"
#include <GameUtilities/Event/Events.h>
#include <GameUtilities/Engin/Engin.h>
#include "Objects/Goal.h"
#include <array>
#include "Resources/ResourceManager.h"
#include "States/States.h"
#include "Events/Events.h"
#include "Macros.h"
#include "Gui/CustomPanel.h"
#include "Gui/CheckboxId.h"
#include "Gui/SliderId.h"
#include "Gui/ComboId.h"
#include "Gui/IntroState/GeneralPanel.h"
#include "Gui/IntroState/VideoPanel.h"
#include <boost/filesystem.hpp>
#include "Box2D/DebugDraw.h"

tgui::Gui StateBase::gui;
sf::Text StateBase::userMessage;
sf::Clock StateBase::messageClock;
sf::Sound StateBase::sound;
sf::Music StateBase::music;

std::shared_ptr<PaddleHud> StateBase::paddle1Hud(new PaddleHud(Settings::paddle1));
std::shared_ptr<PaddleHud> StateBase::paddle2Hud(new PaddleHud(Settings::paddle2));

ContactListener StateBase::contactListener;
sf::Clock StateBase::roundClock;

sf::Texture StateBase::backgroundTexture;
sf::RectangleShape StateBase::backgroundRect;

StateBase::StateBase(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow, std::shared_ptr<Frame> newFrame, DebugDraw &newDebugDraw, const stateId newState):
GU::Engin::GameState(),
engin(newEngin),
window(newWindow),
frame(newFrame),
debugDraw(newDebugDraw),
state(newState),
sysPause(false)
{
    const float &wWidth = window.getView().getSize().x;
    const float &wHeight = window.getView().getSize().y;
    const float &wallTh = Settings::wallThickness;
    float paddleHeight = 100;
    gui.setTarget(window); 
    std::array<sf::Vector2f, 4> horizontalPoints = {sf::Vector2f(0, 0), sf::Vector2f(wWidth, 0), sf::Vector2f(wWidth, wallTh), sf::Vector2f(-wWidth, wallTh)};
    std::array<sf::Vector2f, 4> verticalPoints = {sf::Vector2f(0, 0), sf::Vector2f(wallTh, 0), sf::Vector2f(wallTh, wHeight), sf::Vector2f(0, wHeight)};
    std::array<sf::Vector2f, 4> paddlePoints = {sf::Vector2f(0, 0), sf::Vector2f(wallTh, 0), sf::Vector2f(wallTh, paddleHeight),sf::Vector2f(0, paddleHeight)};
    std::array<sf::Vector2f, 4> goalPoints = {sf::Vector2f(0, 0), sf::Vector2f(wallTh, 0), sf::Vector2f(wallTh, wHeight), sf::Vector2f(0, wHeight)};




    //debugDraw.SetFlags(b2Draw::e_aabbBit | b2Draw::e_jointBit | b2Draw::e_shapeBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);

    frame->world->SetContactListener(&contactListener);
///
    paddle2Hud->setPosition({650, 0});
    gui.add(paddle1Hud);
    gui.add(paddle2Hud);

    music.setLoop(true);
    reset();
}

bool StateBase::isBallOnScreen()
{
    sf::Vector2f pos = frame->ball->getPosition();
    sf::FloatRect windowBounds;
    windowBounds.top = 0;
    windowBounds.left = 0;
    windowBounds.width = Settings::window.dimensions.x;
    windowBounds.height = Settings::window.dimensions.y;

    return windowBounds.contains(pos);

}

void StateBase::Update(GU::Engin::Engin& engin, const float &deltaTime)
{
    UNUSED(engin);
    UNUSED(deltaTime);
    backgroundRect.setSize({window.getView().getSize().x, window.getView().getSize().y});
    if(!IsPaused())
    {

        if(!isBallOnScreen())
        {
            //reset();
        }
        if(roundClock.getElapsedTime().asSeconds() >= 30)
        {
            reset();
        }
    }
}


void StateBase::Draw(GU::Engin::Engin& engin, const float &deltaTime)
{
    UNUSED(engin);
    UNUSED(deltaTime);
    window.clear();
    window.draw(backgroundRect);
    window.draw(*frame->leftPaddle);
    window.draw(*frame->rightPaddle);

    window.draw(*frame->celing);
    window.draw(*frame->leftWall);
    window.draw(*frame->rightWall);
    window.draw(*frame->ground);

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
    int x = rand() % 100 + 50;
    if(rand() % 2 == 0)
        x *= -1;
    int y = rand() % 100 + 50;
    if(rand() % 2 == 0)
       y *= -1;
    
    float paddleOffset = Settings::wallThickness * 4;
    frame->ball->setPosition({Settings::window.dimensions.x / 2, Settings::window.dimensions.y / 2});
    frame->ball->setVelocity({x, y});
    frame->leftPaddle->setPosition(sf::Vector2f(paddleOffset - Settings::wallThickness, Settings::window.dimensions.y / 2));
    frame->rightPaddle->setPosition(sf::Vector2f(Settings::window.dimensions.x - paddleOffset, Settings::window.dimensions.y / 2));
    frame->rightPaddle->handleInput(*frame->ball);
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
    boost::filesystem::path p ("Resources/Backgrounds/");

    boost::filesystem::directory_iterator end_itr;

    for (boost::filesystem::directory_iterator itr(p); itr != end_itr; ++itr)
    {
        if(itr->path().stem().string() == Settings::background)
        {    
            if(backgroundTexture.loadFromFile(itr->path().string()))
            {
                backgroundRect.setTexture(&backgroundTexture);
            }
        }
    }
    music.setVolume(Settings::music.mVolume);
    sound.setVolume(Settings::music.sVolume);
}


void StateBase::sfEvent(GU::Engin::Engin& engin, const sf::Event &event)
{
    switch (event.type)
    {

        case sf::Event::Closed:
            engin.Quit();
            break;
        case sf::Event::Resized:
            {  
                tgui::Widget::Ptr widget = gui.get("PanelPointer");             
                std::shared_ptr<Gui::CustomPanel> temp =  std::dynamic_pointer_cast<Gui::CustomPanel>(widget);
                if(temp) 
                    temp->resize(event.size.width, event.size.height);      
            }
            break; 
        default:
            break;
    }   
}

void StateBase::handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event)
{
    switch(event->id)
    {
        case EventId::LEFT_GOAL_COLLISION:
        {
            int currentScore = Settings::paddle1.score;
	    Settings::paddle1.score = currentScore + 1;
            paddle1Hud->setScore(currentScore + 1);
            reset();
        }
        break;
        case EventId::RIGHT_GOAL_COLLISION:
        {
            int currentScore = Settings::paddle2.score;
	    Settings::paddle2.score = currentScore + 1;
            paddle2Hud->setScore(currentScore + 1);
            reset();
        }
        break;
        case EventId::PLAY_SOUND:
        {
            std::shared_ptr<GU::Evt::PlaySound> temp =  std::dynamic_pointer_cast<GU::Evt::PlaySound>(event);
            if(temp)
            {
                if(ResourceManager::sound.isLoaded(static_cast<soundId>(temp->soundId)))
                {
                    sound.setBuffer(ResourceManager::sound.get(static_cast<soundId>(temp->soundId)));
                    sound.play();
                }
            }
        }
        break;
        case EventId::BALL_COLLISION:
            {
                EventManager::inst().Post<GU::Evt::PlaySound>(static_cast<int>(soundId::BALL));
            }
            break;
        case EventId::PUSH_STATE:
        {
            std::shared_ptr<GU::Evt::PushState> temp =  std::dynamic_pointer_cast<GU::Evt::PushState>(event);
            if(temp)
            {
                switch(temp->id)
                {
                    case stateId::PLAY_STATE:
                        engin.Push<PlayState>(engin, window, frame, debugDraw);
                    break;
                    case stateId::INTRO_STATE:
                        engin.Push<IntroState>(engin, window, frame, debugDraw);
                    break;
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
            }
        }
        break;
        case EventId::ON_CHECK:
            {     
                std::shared_ptr<GU::Evt::OnCheck> temp =  std::dynamic_pointer_cast<GU::Evt::OnCheck>(event);
                if(temp)
                {
                    //debugDraw.CleaFlags();
                   switch(temp->checkboxId)
                   {
                       case checkBoxId::DEBUG_AABB:
                            if(temp->checked)
                               debugDraw.AppendFlags(b2Draw::e_aabbBit); 
                            else
                                debugDraw.ClearFlags(b2Draw::e_aabbBit);
                       break;
                       case checkBoxId::DEBUG_SHAPE:
                            if(temp->checked)
                               debugDraw.AppendFlags(b2Draw::e_shapeBit); 
                            else
                                debugDraw.ClearFlags(b2Draw::e_shapeBit);
                       break;
                       case checkBoxId::DEBUG_MASS:
                            if(temp->checked)
                               debugDraw.AppendFlags(b2Draw::e_centerOfMassBit);
                            else
                                debugDraw.ClearFlags(b2Draw::e_centerOfMassBit);
                       break;
                       case checkBoxId::DEBUG_JOINTS:
                            if(temp->checked)
                                debugDraw.AppendFlags(b2Draw::e_jointBit);
                            else
                                debugDraw.ClearFlags(b2Draw::e_jointBit);
                       break;
                       case checkBoxId::DEBUG_PAIRS:
                            if(temp->checked)
                                debugDraw.AppendFlags(b2Draw::e_pairBit);
                            else
                                debugDraw.ClearFlags(b2Draw::e_pairBit);
                       break;
                   }; 
                }
            }
        break;
        case EventId::SLIDER_CHANGED:
            {     
                std::shared_ptr<GU::Evt::OnSliderChanged> temp =  std::dynamic_pointer_cast<GU::Evt::OnSliderChanged>(event);
                if(temp)
                {
                    switch(temp->sliderId)
                    {
                        case sliderId::SOUND_EFFECTS:
                            sound.setVolume(Settings::music.sVolume);
                            break;
                        case sliderId::MUSIC:
                            music.setVolume(Settings::music.mVolume); 
                            break;
                    }; 
                
                }
            }
        break;
        case EventId::PLAY_MUSIC:
            {    
                std::shared_ptr<GU::Evt::PlayMusic> temp = std::dynamic_pointer_cast<GU::Evt::PlayMusic>(event);
                if(temp)
                {
                    //Load music
                    if(music.openFromFile(temp->musicFile))
                        music.play();
                    else
                       music.stop();
                    
                }
            }
        break;
        case EventId::ON_COMBO_CHANGED:
            {   
                std::shared_ptr<GU::Evt::OnComboChanged> temp = std::dynamic_pointer_cast<GU::Evt::OnComboChanged>(event);
                if(temp)
                {
                   switch(temp->comboId)
                   {
                        case Gui::Combo::comboId::THEME:
                        {
                            switch(temp->index)
                            {
                                case 0:
                                    tgui::Theme::setDefault(nullptr);
                                    Settings::theme = "Default"; 
                                    break;
                                case 1:
                                    tgui::Theme::setDefault("Resources/TGUI/Theme/Black.txt");
                                    Settings::theme = "Black"; 
                                    break;
                                case 2:
                                    tgui::Theme::setDefault("Resources/TGUI/Theme/BabyBlue.txt");
                                    Settings::theme = "Blue"; 
                                    break;
                                    
                            } 
                            gui.removeAllWidgets();
                            tgui::Panel::Ptr cust(new Gui::VideoPanel());
                            std::shared_ptr<Gui::VideoPanel> p = std::dynamic_pointer_cast<Gui::VideoPanel>(cust);
                            p->init(window.getSize().x, window.getSize().y);
                            gui.add(cust, "PanelPointer");
                            } 
                            break;
                        case Gui::Combo::comboId::BACKGROUND:
                            switch(temp->index)
                            {
                                case 0:
                                    if(backgroundTexture.loadFromFile("Resources/Backgrounds/Star.png"))
                                    {
                                        backgroundRect.setTexture(&backgroundTexture);
                                        Settings::background = "Star";
                                    }
                                    break;
                                case 1:
                                    if(backgroundTexture.loadFromFile("Resources/Backgrounds/Nebula.png"))
                                    {
                                        backgroundRect.setTexture(&backgroundTexture);
                                        Settings::background = "Nebula"; 
                                    }
                                    break;
                                    
                            } 
                            gui.removeAllWidgets();
                            tgui::Panel::Ptr cust(new Gui::VideoPanel());
                            std::shared_ptr<Gui::VideoPanel> p = std::dynamic_pointer_cast<Gui::VideoPanel>(cust);
                            p->init(window.getSize().x, window.getSize().y);
                            gui.add(cust, "PanelPointer");
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
