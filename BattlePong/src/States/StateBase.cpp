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
#include <boost/filesystem.hpp>
#include "Box2D/DebugDraw.h"
#include "Gui/ButtonId.h"
#include "Gui/IntroState/GeneralPanel.h"
#include "Gui/IntroState/VideoPanel.h"
#include "Gui/IntroState/IntroGui.h"
#include "Gui/IntroState/OptionsPanel.h"
#include "Gui/IntroState/ControlPanel.h"
#include "Gui/IntroState/DevPanel.h"
#include "Gui/IntroState/SoundPanel.h"
#include "Gui/IntroState/MultiplayerPanel.h"
#include "Gui/IntroState/HostPanel.h"
#include "Gui/IntroState/ConnectPanel.h"
#include "Gui/IntroState/NetworkPanel.h"
#include "Resources/ResourceFunctions.h"

sf::Text StateBase::userMessage;
sf::Clock StateBase::messageClock;
sf::Sound StateBase::sound;

std::shared_ptr<PaddleHud> StateBase::paddle1Hud = nullptr;
std::shared_ptr<PaddleHud> StateBase::paddle2Hud = nullptr;

ContactListener StateBase::contactListener;
sf::Clock StateBase::roundClock;

sf::RectangleShape StateBase::backgroundRect;

StateBase::StateBase(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow, DebugDraw &newDebugDraw, tgui::Gui &newGui, const StateId newState):
GU::Engin::GameState(),
engin(newEngin),
window(newWindow),
debugDraw(newDebugDraw),
gui(newGui),
state(newState),
sysPause(false)
{
    const float &wWidth = window.getView().getSize().x;
    const float &wHeight = window.getView().getSize().y;
    const float &wallTh = Settings::wallThickness;
    float paddleHeight = 100;
    gui.setTarget(window); 


    paddle1Hud.reset(new PaddleHud(Settings::p1Input, Settings::p1Name, Settings::p1Score));
    paddle2Hud.reset(new PaddleHud(Settings::p2Input, Settings::p2Name, Settings::p2Score));


    //debugDraw.SetFlags(b2Draw::e_aabbBit | b2Draw::e_jointBit | b2Draw::e_shapeBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);

///
    paddle2Hud->setPosition({650, 0});
    gui.add(paddle1Hud);
    gui.add(paddle2Hud);

    ResourceManager::getMusic().setLoop(true);
}

bool StateBase::isBallOnScreen(std::shared_ptr<PongFrame> frame)
{
    sf::Vector2f pos = frame->ball->getPosition();
    sf::FloatRect windowBounds;
    windowBounds.top = 0;
    windowBounds.left = 0;
    windowBounds.width = Settings::dimensions.x;
    windowBounds.height = Settings::dimensions.y;

    return windowBounds.contains(pos);

}

void StateBase::Update(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{
    UNUSED(engin);
    UNUSED(deltaTime);
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       //GU::Evt::LogEvent("Pointer should not be null", GU::Evt::LogType::ERROR); 
       return;
    }        
    
    backgroundRect.setSize({window.getView().getSize().x, window.getView().getSize().y});
    if(!IsPaused())
    {

        if(!isBallOnScreen(pongFrame))
        {
            //reset(pongFrame);
        }
        if(roundClock.getElapsedTime().asSeconds() >= 30)
        {
            reset(pongFrame);
        }
    }
}


void StateBase::Draw(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{
    UNUSED(engin);
    UNUSED(deltaTime);
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       //GU::Evt::LogEvent("Pointer should not be null", GU::Evt::LogType::ERROR); 
       return;
    }        
    window.clear();
    window.draw(backgroundRect);
    window.draw(*pongFrame->leftPaddle);
    window.draw(*pongFrame->rightPaddle);

    window.draw(*pongFrame->celing);
    window.draw(*pongFrame->leftWall);
    window.draw(*pongFrame->rightWall);
    window.draw(*pongFrame->ground);

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

void StateBase::reset(std::shared_ptr<PongFrame> frame)
{
    int x = rand() % 100 + 50;
    if(rand() % 2 == 0)
        x *= -1;
    int y = rand() % 100 + 50;
    if(rand() % 2 == 0)
       y *= -1;
   
    float paddleOffset = Settings::wallThickness * 4;
    frame->ball->setPosition({static_cast<float>(window.getView().getSize().x) / 2, static_cast<float>(window.getView().getSize().y) / 2});
    frame->ball->setVelocity({x, y});
    frame->leftPaddle->setPosition(sf::Vector2f(paddleOffset - Settings::wallThickness, static_cast<float>(window.getView().getSize().y) / 2));
    frame->rightPaddle->setPosition(sf::Vector2f(static_cast<float>(window.getView().getSize().x)  - paddleOffset, static_cast<float>(window.getView().getSize().y) / 2));
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

void StateBase::Init(std::shared_ptr<GU::Engin::Frame> frame)
{
    std::cout << "Statebase init" << std::endl;

    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       //GU::Evt::LogEvent("Pointer should not be null", GU::Evt::LogType::ERROR); 
       return;
    }        
    systemPause(false);
    Pause(false);
    ResourceManager::loadBackground("Star.png");

    backgroundRect.setTexture(&ResourceManager::get(textureId::BACKGROUND));
    Settings::background = "Star";
    ResourceManager::getMusic().setVolume(Settings::mVolume);
    sound.setVolume(Settings::sVolume);

    reset(pongFrame);
}


void StateBase::sfEvent(GU::Engin::Engin& engin, const sf::Event &event, std::shared_ptr<GU::Engin::Frame> frame)
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

void StateBase::handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event, std::shared_ptr<GU::Engin::Frame> frame)
{
    
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       //GU::Evt::LogEvent("Pointer should not be null", GU::Evt::LogType::ERROR); 
       return;
    }        
    
    switch(event->id)
    {
        case EventId::CLICK:
            std::shared_ptr<GU::Evt::Click> temp =  std::dynamic_pointer_cast<GU::Evt::Click>(event);
            if(temp)
            {
                switch(temp->buttonId)
                {
                    case Button::id::START:
                        engin.ChangeState<PlayState>(frame, engin, window, debugDraw, gui);
                    break;
                    case Button::id::INTRO_PANEL:
                    {
                    
                        if(Settings::stateId == StateId::PLAY_STATE)
                        {
                            engin.ChangeState<IntroState>(frame, engin, window, debugDraw, gui);
                        }
                        else
                        { 
                            gui.removeAllWidgets();
                            StateBase::Init(pongFrame);
                            tgui::Panel::Ptr cust(new IntroGui());
                            std::shared_ptr<IntroGui> p = std::dynamic_pointer_cast<IntroGui>(cust);
                            p->init(window.getSize().x, window.getSize().y);
                            gui.add(cust, "PanelPointer");
                        }
                    }
                    break;
		    case Button::id::OPTIONS:
                    case Button::id::GENERAL_TAB:
                    {
                        gui.removeAllWidgets();
                        StateBase::Init(pongFrame);
                        tgui::Panel::Ptr cust(new Gui::GeneralPanel());
                        std::shared_ptr<Gui::GeneralPanel> p = std::dynamic_pointer_cast<Gui::GeneralPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                    }
                    break;
                    case Button::id::CONTROLS_TAB:
                    {
                        gui.removeAllWidgets();
                        StateBase::Init(pongFrame);
                        tgui::Panel::Ptr cust(new Gui::ControlPanel(nullptr));
                        std::shared_ptr<Gui::ControlPanel> p = std::dynamic_pointer_cast<Gui::ControlPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                    }
                    break;
                    case Button::id::VIDEO_TAB:
                     {
                        gui.removeAllWidgets();
                        StateBase::Init(pongFrame);
                        tgui::Panel::Ptr cust(new Gui::VideoPanel());
                        std::shared_ptr<Gui::VideoPanel> p = std::dynamic_pointer_cast<Gui::VideoPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                    }
                    break;
                    case Button::id::SOUND_TAB:
                     {
                        gui.removeAllWidgets();
                        StateBase::Init(pongFrame);
                        tgui::Panel::Ptr cust(new Gui::SoundPanel(nullptr));
                        std::shared_ptr<Gui::SoundPanel> p = std::dynamic_pointer_cast<Gui::SoundPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                    }
                    break;
                    case Button::id::NETWORK_TAB:
                     {
                        gui.removeAllWidgets();
                        StateBase::Init(pongFrame);
                        tgui::Panel::Ptr cust(new Gui::NetworkPanel());
                        std::shared_ptr<Gui::NetworkPanel> p = std::dynamic_pointer_cast<Gui::NetworkPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                    }
                    break;
                    case Button::id::DEV_TAB:
                     {
                        gui.removeAllWidgets();
                        StateBase::Init(pongFrame);
                        tgui::Panel::Ptr cust(new Gui::DevPanel());
                        std::shared_ptr<Gui::DevPanel> p = std::dynamic_pointer_cast<Gui::DevPanel>(cust);
                        p->init(debugDraw.GetFlags(), window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                    }
                    break;
                    case Button::id::MULTIPLAYER:
                     {
                        gui.removeAllWidgets();
                        StateBase::Init(pongFrame);
                        tgui::Panel::Ptr cust(new MultiplayerPanel());
                        std::shared_ptr<MultiplayerPanel> p = std::dynamic_pointer_cast<MultiplayerPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                    }
                    break;
                    case Button::id::HOST:
                     {
                        gui.removeAllWidgets();
                        StateBase::Init(pongFrame);
                        tgui::Panel::Ptr cust(new HostPanel());
                        std::shared_ptr<HostPanel> p = std::dynamic_pointer_cast<HostPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                     }
                    break;
                    case Button::id::CONNECT:
                    {
                        gui.removeAllWidgets();
                        StateBase::Init(pongFrame);
                        tgui::Panel::Ptr cust(new ConnectPanel());
                        std::shared_ptr<ConnectPanel> p = std::dynamic_pointer_cast<ConnectPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y); 
                        gui.add(cust, "PanelPointer");
                        
                    }

                }
            }

        break;
    }
    
    switch(event->id)
    {
        case EventId::LEFT_GOAL_COLLISION:
        {
            int currentScore = Settings::p1Score;
	        Settings::p1Score = currentScore + 1;
            paddle1Hud->setScore(currentScore + 1);
            reset(pongFrame);
        }
        break;
        case EventId::RIGHT_GOAL_COLLISION:
        {
            int currentScore = Settings::p2Score;
	    Settings::p2Score = currentScore + 1;
            paddle2Hud->setScore(currentScore + 1);
            reset(pongFrame);
        }
        break;
        case EventId::PLAY_SOUND:
        {
            std::shared_ptr<GU::Evt::PlaySound> temp =  std::dynamic_pointer_cast<GU::Evt::PlaySound>(event);
            if(temp)
            {
                if(ResourceManager::isLoaded(static_cast<soundId>(temp->soundId)))
                {
                    sound.setBuffer(ResourceManager::get(static_cast<soundId>(temp->soundId)));
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
                    case StateId::PLAY_STATE:
                        engin.Push<PlayState>(frame, engin, window, debugDraw, gui);
                    break;
                    case StateId::INTRO_STATE:
                        engin.Push<IntroState>(frame, engin, window, debugDraw, gui);
                    break;
                }
            }

        break;
        }
        case EventId::POP_STATE:
            engin.Pop(frame);
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
                            sound.setVolume(Settings::sVolume);
                            break;
                        case sliderId::MUSIC:
			    ResourceManager::getMusic().setVolume(Settings::mVolume); 
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
                    if(ResourceManager::loadMusic(temp->musicFile))
                        ResourceManager::getMusic().play(); 
		    else
                        ResourceManager::getMusic().stop(); 
                    
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
					ResourceManager::loadTheme("Default"); 
                                    break;
                                case 1:
				    ResourceManager::loadTheme("Black");
                                    break;
                                case 2:
				    ResourceManager::loadTheme("BabyBlue"); 
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
				    ResourceManager::loadBackground("Star.png"); 
                                    backgroundRect.setTexture(&ResourceManager::get(textureId::BACKGROUND));
                                    Settings::background = "Star";
                                    break;
                                case 1:
				    ResourceManager::loadBackground("Nebula.png"); 
                                    backgroundRect.setTexture(&ResourceManager::get(textureId::BACKGROUND));
                                    Settings::background = "Nebula"; 
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
