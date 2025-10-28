#include "Engin/States/StateBase.h"
#include "Engin/States/States.h"
#include "Settings.h"
#include "Objects/Ball.h"
#include "Objects/Wall.h"
#include "Objects/Paddle.h"
#include "Input/AI.h"
#include <GameUtilities/Event/Events.h>
#include <GameUtilities/Engin/Engin.h>
#include <GameUtilities/Engin/Engin.h>
#include <GameUtilities/Event/Events/OnLog.h>
#include <GameUtilities/Event/Events/Widget/OnTextChanged.h>
#include <GameUtilities/Log/LogEntry.h>
#include <GameUtilities/Log/Component/Components.h>
#include "Objects/Goal.h"
#include <array>
#include "Resources/ResourceManager.h"
#include "Resources/Images/Black/Battle Pong.h"
#include "Resources/Images/Default/Battle Pong.h"
#include "Resources/Images/BabyBlue/Battle Pong.h"
#include "Resources/Images/Backgrounds/Star.h"
#include "Resources/Images/Backgrounds/Nebula.h"
#include "Events/Events.h"
#include "Macros.h"
#include "Gui/CustomPanel.h"
#include "Gui/GuiId.h"
#include <boost/filesystem.hpp>
#include "Box2D/DebugDraw.h"
#include "Gui/GuiId.h"
#include "Gui/OptionsPanel/GeneralPanel.h"
#include "Gui/OptionsPanel/VideoPanel.h"
#include "Gui/IntroPanel.h"
#include "Gui/OptionsPanel/OptionsPanel.h"
#include "Gui/OptionsPanel/ControlPanel.h"
#include "Gui/OptionsPanel/DevPanel.h"
#include "Gui/OptionsPanel/SoundPanel.h"
#include "Gui/OptionsPanel/MultiplayerPanel.h"
#include "Gui/OptionsPanel/HostPanel.h"
#include "Gui/OptionsPanel/ConnectPanel.h"
#include "Gui/OptionsPanel/NetworkPanel.h"
#include "Engin/Game.h"
#include "Log.h"
#include <string>
#include "WriteLog.h"

sf::Clock StateBase::messageClock;
sf::Sound StateBase::sound;


ContactListener StateBase::contactListener;
sf::Clock StateBase::collisionClock;

sf::RectangleShape StateBase::backgroundRect;

StateBase::StateBase(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow, DebugDraw &newDebugDraw, tgui::Gui &newGui, const StateId newState):
GU::Engin::GameState(),
engin(newEngin),
window(newWindow),
debugDraw(newDebugDraw),
gui(newGui),
state(newState)
{
    BP_LOG_TRACE(__FUNCTION__)
    gui.setTarget(window);


    ResourceManager::getMusic().setLoop(true);
}


void StateBase::update(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    UNUSED(engin);
    UNUSED(deltaTime);
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       BP_LOG_FATAL_ERROR("Pointer should not be null")
       return;
    }

    backgroundRect.setSize({window.getView().getSize().x, window.getView().getSize().y});
    if(!Settings::playerPaused && !Settings::clientPaused)
    {

        if(!Settings::multiplayer || Settings::isHost)
        {
            if(collisionClock.getElapsedTime().asSeconds() >= Settings::collisionTime)
            {
                EventManager::inst().post<GU::Evt::OnClick>(Gui::id::RESET);
            }
        }
    }
    
    if(!Settings::multiplayer || Settings::isHost)
    {
        const int SECONDS = 1;
        
        //Text is Ready!
        if(pongFrame->userMessageIndex == 4)
        {
            if(messageClock.getElapsedTime().asSeconds() > SECONDS)
            {
                pongFrame->userMessageIndex = 3;
                centerText(frame);
                messageClock.restart();
                Settings::systemPaused = true; 
                EventManager::inst().post<GU::Evt::OnPlaySound>(static_cast<int>(soundId::BALL), __LINE__, __FILE__);
            }
        }
        else if(pongFrame->userMessageIndex == 3)
        {
            if(messageClock.getElapsedTime().asSeconds() > SECONDS)
            {
                pongFrame->userMessageIndex = 2;
                centerText(frame);
                messageClock.restart();
                Settings::systemPaused = true; 
                EventManager::inst().post<GU::Evt::OnPlaySound>(static_cast<int>(soundId::BALL), __LINE__, __FILE__);
            }
        }
        else if(pongFrame->userMessageIndex == 2)
        {
            if(messageClock.getElapsedTime().asSeconds() > SECONDS)
            {
                pongFrame->userMessageIndex = 1;
                centerText(frame);
                messageClock.restart();
                Settings::systemPaused = true; 
                EventManager::inst().post<GU::Evt::OnPlaySound>(static_cast<int>(soundId::BALL), __LINE__, __FILE__);
            }
        }
        else if(pongFrame->userMessageIndex == 1)
        {
            if(messageClock.getElapsedTime().asSeconds() > SECONDS)
            {
                pongFrame->userMessageIndex = 5;
                centerText(frame);
                messageClock.restart();
                Settings::systemPaused = true; 
                EventManager::inst().post<GU::Evt::OnPlaySound>(static_cast<int>(soundId::BALL), __LINE__, __FILE__);
            }
        }
        else if(pongFrame->userMessageIndex == 5)
        {
            if(messageClock.getElapsedTime().asSeconds() > SECONDS)
            {
                pongFrame->userMessageIndex = 0;
                messageClock.restart();
                Settings::systemPaused = false;
            }
        }
    }
}


void StateBase::draw(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    UNUSED(engin);
    UNUSED(deltaTime);
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       BP_LOG_FATAL_ERROR("Pointer should not be null")
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
    window.draw(pongFrame->userMessage[pongFrame->userMessageIndex]);
    #ifdef DEBUG
        window.draw(debugDraw);
    #endif

    gui.draw();
}


void StateBase::reset(std::shared_ptr<PongFrame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    int x = rand() % 100 + 50;
    if(rand() % 2 == 0)
        x *= -1;
    int y = rand() % 100 + 50;
    if(rand() % 2 == 0)
       y *= -1;

    frame->ball->setPosition({Settings::dimensions.x / 2, Settings::dimensions.y / 2});
    frame->ball->setVelocity({static_cast<float>(x), static_cast<float>(y)});
    frame->leftPaddle->setPosition(sf::Vector2f(Settings::paddleOffset + Settings::wallThickness, Settings::dimensions.y / 2));
    frame->rightPaddle->setPosition({Settings::dimensions.x  - Settings::paddleOffset - Settings::wallThickness - Settings::paddleThickness, Settings::dimensions.y / 2});
    frame->rightPaddle->handleInput(*frame->ball);
    pongFrame->userMessageIndex = 4;
    centerText(frame);
    messageClock.restart();
    collisionClock.restart();
    Settings::systemPaused = true;
}


void StateBase::centerText(std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       BP_LOG_FATAL_ERROR("Pointer should not be null")
       return;
    }

    for(std::size_t i = 0; i < pongFrame->userMessage.size(); ++i)
    {
        sf::FloatRect bounds = pongFrame->userMessage[i].getGlobalBounds();

        float originX = bounds.width / 2;
        float originY = bounds.height / 2;

        pongFrame->userMessage[i].setOrigin({originX, originY});
        pongFrame->userMessage[i].setPosition({window.getView().getCenter().x, window.getView().getCenter().y});
    }

}

void StateBase::init(GU::Engin::Engin& engin, std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       BP_LOG_FATAL_ERROR("Pointer should not be null")
       return;
    }
   
//    pongFrame->userMessage.setString(""); 
   
    ResourceManager resourceManager;
    resourceManager.loadFont(fontId::MONOSPACE, "Monospace"); 

    for(std::size_t i = 0; i < pongFrame->userMessage.size(); ++i)
    {
        pongFrame->userMessage[i].setFont(resourceManager.get(fontId::MONOSPACE));
    }
    if(Settings::currentBackground == "Star")
        ResourceManager::loadBackground(Star_png, Star_png_len);
    else if(Settings::currentBackground == "Nebula")
        ResourceManager::loadBackground(Nebula_png, Nebula_png_len);
            
    backgroundRect.setTexture(&ResourceManager::get(textureId::BACKGROUND));
    backgroundRect.setSize({window.getView().getSize().x, window.getView().getSize().y});

    ResourceManager::getMusic().setVolume(Settings::musicVolume);
    sound.setVolume(Settings::soundVolume);
    
    gui.add(pongFrame->paddle1Hud);
    gui.add(pongFrame->paddle2Hud);

}


void StateBase::sfEvent(GU::Engin::Engin& engin, const sf::Event &event, std::shared_ptr<GU::Engin::Frame> frame)
{
    UNUSED(frame);

    switch (event.type)
    {
        case sf::Event::Closed:
        {
            Game *game = static_cast<Game*>(&engin);

            if(game->hostSend.server.isConnected())
                game->hostSend.server.disconnect();
            if(game->hostSend.client.isConnected())
                game->hostSend.client.disconnect();
            engin.quit();
        }
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
        {
            //Default case
            BP_LOG_WARNING("Default case triggered");
        }
        break;
    }
}

void StateBase::handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event, std::shared_ptr<GU::Engin::Frame> frame)
{
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
        BP_LOG_FATAL_ERROR("Pointer should not be null")
        return;
    }

    switch(event->getId())
    {
        case EventId::LOG:
        {
            Game *game = static_cast<Game*>(&engin);
            WriteLog::write(*game, event);
        }
        break;
        case EventId::CLICK:
        {
            std::shared_ptr<GU::Evt::OnClick> temp =  std::dynamic_pointer_cast<GU::Evt::OnClick>(event);
            if(temp)
            {
                switch(temp->m_buttonId)
                {
                    case Gui::id::START:
                        engin.push<PlayState>(frame, engin, window, debugDraw, gui);
                    break;
                    case Gui::id::MULTIPLAYER_PANEL_BACK:
                    case Gui::id::OPTIONS_PANEL_BACK:
                    case Gui::id::INTRO_PANEL:
                    {
                        gui.removeAllWidgets();
                        StateBase::init(engin, pongFrame);
                        tgui::Panel::Ptr cust(new Gui::IntroPanel());
                        std::shared_ptr<Gui::IntroPanel> p = std::dynamic_pointer_cast<Gui::IntroPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                        gui.add(pongFrame->paddle1Hud);
                        gui.add(pongFrame->paddle2Hud);
                    }
                    break;
		            case Gui::id::OPTIONS:
                    case Gui::id::GENERAL_TAB:
                    {
                        gui.removeAllWidgets();
                        tgui::Panel::Ptr cust(new Gui::GeneralPanel());
                        std::shared_ptr<Gui::GeneralPanel> p = std::dynamic_pointer_cast<Gui::GeneralPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                        gui.add(pongFrame->paddle1Hud);
                        gui.add(pongFrame->paddle2Hud);
                    }
                    break;
                    case Gui::id::CONTROLS_TAB:
                    {
                        gui.removeAllWidgets();
                        tgui::Panel::Ptr cust(new Gui::ControlPanel(nullptr));
                        std::shared_ptr<Gui::ControlPanel> p = std::dynamic_pointer_cast<Gui::ControlPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                        gui.add(pongFrame->paddle1Hud);
                        gui.add(pongFrame->paddle2Hud);
                    }
                    break;
                    case Gui::id::VIDEO_TAB:
                    {
                        gui.removeAllWidgets();
                        tgui::Panel::Ptr cust(new Gui::VideoPanel());
                        std::shared_ptr<Gui::VideoPanel> p = std::dynamic_pointer_cast<Gui::VideoPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                        gui.add(pongFrame->paddle1Hud);
                        gui.add(pongFrame->paddle2Hud);
                    }
                    break;
                    case Gui::id::SOUND_TAB:
                    {
                        gui.removeAllWidgets();
                        tgui::Panel::Ptr cust(new Gui::SoundPanel(nullptr));
                        std::shared_ptr<Gui::SoundPanel> p = std::dynamic_pointer_cast<Gui::SoundPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                        gui.add(pongFrame->paddle1Hud);
                        gui.add(pongFrame->paddle2Hud);
                    }
                    break;
                    case Gui::id::NETWORK_TAB:
                    {
                        gui.removeAllWidgets();
                        tgui::Panel::Ptr cust(new Gui::NetworkPanel());
                        std::shared_ptr<Gui::NetworkPanel> p = std::dynamic_pointer_cast<Gui::NetworkPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                        gui.add(pongFrame->paddle1Hud);
                        gui.add(pongFrame->paddle2Hud);
                    }
                    break;
                    case Gui::id::DEV_TAB:
                    {
                        gui.removeAllWidgets();
                        tgui::Panel::Ptr cust(new Gui::DevPanel());
                        std::shared_ptr<Gui::DevPanel> p = std::dynamic_pointer_cast<Gui::DevPanel>(cust);
                        p->init(debugDraw.GetFlags(), window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                        gui.add(pongFrame->paddle1Hud);
                        gui.add(pongFrame->paddle2Hud);
                    }
                    break;
                    case Gui::id::HOST_PANEL_BACK:
                    case Gui::id::CONNECT_PANEL_BACK:
                    case Gui::id::MULTIPLAYER:
                    {
                        gui.removeAllWidgets();
                        tgui::Panel::Ptr cust(new Gui::MultiplayerPanel());
                        std::shared_ptr<Gui::MultiplayerPanel> p = std::dynamic_pointer_cast<Gui::MultiplayerPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                        gui.add(pongFrame->paddle1Hud);
                        gui.add(pongFrame->paddle2Hud);
                    }
                    break;
                    case Gui::id::HOST:
                    {
                        gui.removeAllWidgets();
                        tgui::Panel::Ptr cust(new Gui::HostPanel());
                        std::shared_ptr<Gui::HostPanel> p = std::dynamic_pointer_cast<Gui::HostPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                        gui.add(pongFrame->paddle1Hud);
                        gui.add(pongFrame->paddle2Hud);
                    }
                    break;
                    case Gui::id::CONNECT:
                    {
                        gui.removeAllWidgets();
                        tgui::Panel::Ptr cust(new Gui::ConnectPanel());
                        std::shared_ptr<Gui::ConnectPanel> p = std::dynamic_pointer_cast<Gui::ConnectPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                        gui.add(pongFrame->paddle1Hud);
                        gui.add(pongFrame->paddle2Hud);

                    }
                    break;
                    case Gui::id::CREDITS:
                      engin.push<CreditsState>(frame, engin, window, debugDraw, gui);
                    break;
                    case Gui::id::LICENSE:
                      engin.push<LicenseState>(frame, engin, window, debugDraw, gui);
                    break;
                    case Gui::id::BACK:
                    {
                        Game *game = static_cast<Game*>(&engin);
                        game->setPop(true);
                    } 
                    return;
                    case Gui::id::EXIT:
                    {
                        Game *game = static_cast<Game*>(&engin);
                        game->quit();
                    } 
                    break;
                    case Gui::id::RESET:
                    {
                        reset(pongFrame);
                    }
                    break;
                }
            }
        }
        break;
        case EventId::ON_TEXT_CHANGED:
        {
            std::shared_ptr<GU::Evt::OnTextChanged> temp =  std::dynamic_pointer_cast<GU::Evt::OnTextChanged>(event);
            if(temp)
            {
                switch(temp->m_widgetId)
                {

                    case Gui::id::VELOCITY_ITERATIONS:
                    {
                        Settings::velocityIterations = int(temp->m_text[0] - '0'); 
                    } 
                    break;
                    case Gui::id::POSITION_ITERATIONS:
                    {
                        Settings::positionIterations = int(temp->m_text[0] - '0'); 
                    } 
                    break;
                    case Gui::id::FRAME_RATE:
                    {
                        Settings::frameRate = std::stoi(temp->m_text.c_str());
                    } 
                    break;
                    case Gui::id::BALL_SPEED:
                    {
                        Settings::ballSpeed = std::stoi(temp->m_text.c_str());
                    } 
                    break;
                    case Gui::id::PADDLE_SPEED:
                    {
                        Settings::paddleSpeed = std::stoi(temp->m_text.c_str());
                    } 
                    break;
                    case Gui::id::WALL_THICKNESS:
                    {
                        Settings::wallThickness = std::stoi(temp->m_text.c_str());
                    } 
                    break;
                    case Gui::id::BALL_RADIUS:
                    {
                        Settings::ballRadius = std::stoi(temp->m_text.c_str());
                    } 
                    break;
                    case Gui::id::PORT:
                    {
                        Settings::port = std::stoi(temp->m_text.c_str());
                    } 
                    break;
                    case Gui::id::PLAYER_TITLE:
                    {
                        if (Settings::isClient)
                        {
                            Settings::rightPaddleTitle = temp->m_text;
                            pongFrame->paddle2Hud->setScore(pongFrame->paddle2Hud->getScore(), Settings::rightPaddleTitle);
                        }
                        else 
                        {
                            Settings::leftPaddleTitle = temp->m_text; 
                            pongFrame->paddle1Hud->setScore(pongFrame->paddle1Hud->getScore(), Settings::leftPaddleTitle);
                        }
                    } 
                    break;
                }
            }
        }
        break;
        case EventId::LEFT_GOAL_COLLISION:
        {
            int currentScore = Settings::p1Score;
	        Settings::p1Score = currentScore + 1;
            pongFrame->paddle1Hud->setScore(currentScore + 1, Settings::leftPaddleTitle);
            EventManager::inst().post<GU::Evt::OnClick>(Gui::id::RESET);
        }
        break;
        case EventId::RIGHT_GOAL_COLLISION:
        {
            int currentScore = Settings::p2Score;
	        Settings::p2Score = currentScore + 1;
            pongFrame->paddle2Hud->setScore(currentScore + 1, Settings::rightPaddleTitle);
            EventManager::inst().post<GU::Evt::OnClick>(Gui::id::RESET);
        }
        break;
        case EventId::PLAY_SOUND:
        {
            std::shared_ptr<GU::Evt::OnPlaySound> temp =  std::dynamic_pointer_cast<GU::Evt::OnPlaySound>(event);
            if(temp)
            {
                if(ResourceManager::isLoaded(static_cast<soundId>(temp->m_soundId)))
                {
                    sound.setBuffer(ResourceManager::get(static_cast<soundId>(temp->m_soundId)));
                    sound.play();
                }
            }
        }
        break;
        case EventId::BALL_COLLISION:
        {
            EventManager::inst().post<GU::Evt::OnPlaySound>(static_cast<int>(soundId::BALL));
            collisionClock.restart();
        }
        break;
        case EventId::PUSH_STATE:
        {
            std::shared_ptr<GU::Evt::OnPushState> temp =  std::dynamic_pointer_cast<GU::Evt::OnPushState>(event);
            if(temp)
            {
                switch(temp->getId())
                {
                    case StateId::PLAY_STATE:
                        engin.push<PlayState>(frame, engin, window, debugDraw, gui);
                    break;
                    case StateId::INTRO_STATE:
                        engin.push<IntroState>(frame, engin, window, debugDraw, gui);
                    break;
                }
            }
        }
        break;
        case EventId::POP_STATE:
        {
            engin.pop(frame);
        } 
        break;
        case EventId::CHANGE_STATE:
        {
            std::shared_ptr<GU::Evt::OnChangeState> temp =  std::dynamic_pointer_cast<GU::Evt::OnChangeState>(event);
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
                switch(temp->m_widgetId)
                {
                    case Gui::DEBUG_AABB:
                    {
                        if(temp->m_checked)
                        {
                            debugDraw.AppendFlags(b2Draw::e_aabbBit);
                            Settings::b2aabb = true;
                        }
                        else
                        {
                            debugDraw.ClearFlags(b2Draw::e_aabbBit);
                            Settings::b2aabb = false;
                        }
                    }
                    break;
                    case Gui::DEBUG_SHAPE:
                    { 
                        if(temp->m_checked)
                        {
                            debugDraw.AppendFlags(b2Draw::e_shapeBit);
                            Settings::b2shapes = true;
                        }
                        else
                        {
                            debugDraw.ClearFlags(b2Draw::e_shapeBit);
                            Settings::b2shapes = false;
                        }
                    } 
                    break;
                    case Gui::DEBUG_MASS:
                    { 
                        if(temp->m_checked)
                        {
                            debugDraw.AppendFlags(b2Draw::e_centerOfMassBit);
                            Settings::b2centerOfMass = true;
                        }
                        else
                        {
                            debugDraw.ClearFlags(b2Draw::e_centerOfMassBit);
                            Settings::b2centerOfMass = false;
                        }
                    } 
                    break;
                    case Gui::DEBUG_JOINTS:
                    { 
                        if(temp->m_checked)
                        {
                            debugDraw.AppendFlags(b2Draw::e_jointBit);
                            Settings::b2joints = true;
                        }
                        else
                        {
                            debugDraw.ClearFlags(b2Draw::e_jointBit);
                            Settings::b2joints = false;
                        }
                    } 
                    break;
                    case Gui::DEBUG_PAIRS:
                    { 
                        if(temp->m_checked)
                        {
                            debugDraw.AppendFlags(b2Draw::e_pairBit);
                            Settings::b2pair = true;
                        }
                        else
                        {
                            debugDraw.ClearFlags(b2Draw::e_pairBit);
                            Settings::b2pair = false;
                        }
                    } 
                    break;
                    case Gui::DEBUG_LOG:
                        BP_LOG_WARNING("Debug Log not implimented");
                    break;
                    case Gui::DEBUG_PAUSE:
                        Settings::playerPaused = temp->m_checked;
                    break;
                    case Gui::DEBUG_SYSTEM_PAUSE:
                        Settings::systemPaused = temp->m_checked;
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
                switch(temp->m_widgetId)
                {
                    case Gui::id::SOUND_EFFECTS:
                    {
                        sound.setVolume(Settings::soundVolume);
                    } 
                    break;
                    case Gui::id::MUSIC:
			        { 
                        ResourceManager::getMusic().setVolume(Settings::musicVolume);
                    } 
                    break;
                };

            }
        }
        break;
        case EventId::PLAY_MUSIC:
        {
            BP_LOG_WARNING("PLAY_MUSIC not implimented");
        }
        break;
        case EventId::ON_ITEM_SELECTED:
        {
            std::shared_ptr<GU::Evt::OnItemSelected> temp = std::dynamic_pointer_cast<GU::Evt::OnItemSelected>(event);
            if(temp)
            {
                switch(temp->m_widgetId)
                {
                    case Gui::id::THEME:
                    {
                        ResourceManager::loadTheme(Settings::themes[temp->m_index]);
                        Settings::currentTheme = Settings::themes[temp->m_index];
                        gui.removeAllWidgets();
                        tgui::Panel::Ptr cust(new Gui::VideoPanel());
                        std::shared_ptr<Gui::VideoPanel> p = std::dynamic_pointer_cast<Gui::VideoPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                    }
                    break;
                    case Gui::id::BACKGROUND:
                    {
                         Settings::currentBackground = Settings::backgrounds[temp->m_index];
                        if(Settings::currentBackground == "Star")
                            ResourceManager::loadBackground(Star_png, Star_png_len);
                        else if(Settings::currentBackground == "Nebula")
                            ResourceManager::loadBackground(Nebula_png, Nebula_png_len);
                                
                        backgroundRect.setTexture(&ResourceManager::get(textureId::BACKGROUND));
                        backgroundRect.setSize({window.getView().getSize().x, window.getView().getSize().y});
                        
                        backgroundRect.setSize({window.getView().getSize().x, window.getView().getSize().y});
                        backgroundRect.setTexture(&ResourceManager::get(textureId::BACKGROUND));

                        gui.removeAllWidgets();
                        tgui::Panel::Ptr cust(new Gui::VideoPanel());
                        std::shared_ptr<Gui::VideoPanel> p = std::dynamic_pointer_cast<Gui::VideoPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                    } 
                    break;
                    case Gui::id::MUSIC_COMBO:
                    {
                        ResourceManager::loadMusic(Settings::songList[temp->m_index]);
                        ResourceManager::getMusic().play();
                        Settings::currentSong = temp->m_index;
                    } 
                    break;
                    case Gui::id::RESOLUTION:
                    {
                        Game *game = static_cast<Game*>(&engin);
                        game->m_resolution = true;
                    } 
                    break;
                }
            }
        }
        break;
    }
}


StateBase::~StateBase()
{
    BP_LOG_TRACE(__FUNCTION__)
}
