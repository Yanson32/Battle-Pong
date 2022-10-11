#include "States/StateBase.h"
#include "Settings.h"
#include "Objects/Ball.h"
#include "Objects/Wall.h"
#include "Objects/Paddle.h"
#include "Input/AI.h"
#include <GameUtilities/Event/Events.h>
#include <GameUtilities/Engin/Engin.h>
#include <GameUtilities/Engin/Engin.h>
#include <GameUtilities/Event/Events/OnLog.h>
#include <GameUtilities/Event/OnTextChanged.h>
#include <GameUtilities/Log/LogEntry.h>
#include <GameUtilities/Log/Component/Components.h>
#include <GameUtilities/Core/PreferencesManager.h>
#include "Objects/Goal.h"
#include <array>
#include "Resources/ResourceManager.h"
#include "States/States.h"
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
#include "Game.h"
#include "Log.h"
#include <string>

sf::Text StateBase::userMessage;
sf::Clock StateBase::messageClock;
sf::Sound StateBase::sound;

std::shared_ptr<Gui::PaddleHud> StateBase::paddle1Hud = nullptr;
std::shared_ptr<Gui::PaddleHud> StateBase::paddle2Hud = nullptr;

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
    BP_LOG_TRACE(__FUNCTION__)
    gui.setTarget(window);

    paddle1Hud.reset(new Gui::PaddleHud(Settings::p1Input, Settings::p1Name, Settings::p1Score));
    paddle2Hud.reset(new Gui::PaddleHud(Settings::p2Input, Settings::p2Name, Settings::p2Score));

    paddle2Hud->setPosition({650, 0});
    gui.add(paddle1Hud);
    gui.add(paddle2Hud);

    ResourceManager::getMusic().setLoop(true);
}

bool StateBase::isBallOnScreen(std::shared_ptr<PongFrame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    sf::Vector2f pos = frame->ball->getPosition();
    sf::FloatRect windowBounds;
    windowBounds.top = 0;
    windowBounds.left = 0;
    windowBounds.width = Settings::dimensions.x;
    windowBounds.height = Settings::dimensions.y;

    return windowBounds.contains(pos);

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
    if(!isPaused())
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

    #ifdef DEBUG
        window.draw(debugDraw);
    #endif

    gui.draw();
}

void StateBase::systemPause(const bool newSysPause)
{
    BP_LOG_TRACE(__FUNCTION__)
    sysPause = newSysPause;
}

bool StateBase::isSystemPaused() const
{
    BP_LOG_TRACE(__FUNCTION__)
    return sysPause;
}

void StateBase::reset(std::shared_ptr<PongFrame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    int x = rand() % 100 + 50;
    if(rand() % 2 == 0)
        x *= -1;
    int y = rand() % 100 + 50;
    if(rand() % 2 == 0)
       y *= -1;

    float paddleOffset = Settings::wallThickness * 4;
    frame->ball->setPosition({static_cast<float>(window.getView().getSize().x) / 2, static_cast<float>(window.getView().getSize().y) / 2});
    frame->ball->setVelocity({static_cast<float>(x), static_cast<float>(y)});
    frame->leftPaddle->setPosition(sf::Vector2f(paddleOffset - Settings::wallThickness, static_cast<float>(window.getView().getSize().y) / 2));
    frame->rightPaddle->setPosition(sf::Vector2f(static_cast<float>(window.getView().getSize().x)  - paddleOffset, static_cast<float>(window.getView().getSize().y) / 2));
    frame->rightPaddle->handleInput(*frame->ball);
    userMessage.setString("Ready!");
    centerText();
    messageClock.restart();
    roundClock.restart();
    systemPause(true);
}


void StateBase::centerText()
{
    BP_LOG_TRACE(__FUNCTION__)
    sf::FloatRect bounds = userMessage.getGlobalBounds();

    float originX = bounds.width / 2;
    float originY = bounds.height / 2;

    userMessage.setOrigin({originX, originY});

}

void StateBase::init(std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)

    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       BP_LOG_FATAL_ERROR("Pointer should not be null")
       return;
    }
    systemPause(false);
    pause(false);
    ResourceManager::loadBackground("Star.png");

    backgroundRect.setTexture(&ResourceManager::get(textureId::BACKGROUND));
    Settings::background = "Star";
    ResourceManager::getMusic().setVolume(Settings::musicVolume);
    sound.setVolume(Settings::soundVolume);

    reset(pongFrame);
}


void StateBase::sfEvent(GU::Engin::Engin& engin, const sf::Event &event, std::shared_ptr<GU::Engin::Frame> frame)
{
    UNUSED(frame);

    switch (event.type)
    {
        case sf::Event::Closed:
            engin.quit();
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
            std::shared_ptr<GU::Evt::OnLog> temp =  std::dynamic_pointer_cast<GU::Evt::OnLog>(event);
            Game *game = static_cast<Game*>(&engin);
            std::shared_ptr<GU::Log::LogEntry> entry(new GU::Log::LogEntry());
            entry->add<GU::Log::MsgComponent>(temp->getMessage());
            entry->add<GU::Log::SeverityComponent>(static_cast<GU::Log::LogType>(temp->getSeverity()));
            entry->add<GU::Log::LineComponent>(temp->getLine());
            entry->add<GU::Log::FileComponent>(temp->getFile());

            if(temp->getSeverity() > Settings::logSeverity)
                return;

            if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_FATAL_ERROR))
            {
                game->logManager.write(entry);
                exit(1);
            }
            else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_ERROR))
                game->logManager.write(entry);
            else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_WARNING))
            {
                static int count = 0;
                if(count == 0)
                {
                    std::cout << "Log Warning is broken" << std::endl; 
                    ++count;
                }
                //game->logManager.write(entry);
            }
            else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_MESSAGE))
                game->logManager.write(entry);
            else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_VERBOSE))
                game->logManager.write(entry);
            else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_STATUS))
                game->logManager.write(entry);
            else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_SYSTEM_ERROR))
                game->logManager.write(entry);
            else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_DEBUG))
                game->logManager.write(entry);
            else if(temp->getSeverity() == static_cast<int>(GU::Log::LogType::GU_TRACE))
            {
                game->logManager.write(entry);
            }

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
                        StateBase::init(pongFrame);
                        tgui::Panel::Ptr cust(new Gui::IntroPanel());
                        std::shared_ptr<Gui::IntroPanel> p = std::dynamic_pointer_cast<Gui::IntroPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
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
                    }
                    break;
                    case Gui::id::CONTROLS_TAB:
                    {
                        gui.removeAllWidgets();
                        tgui::Panel::Ptr cust(new Gui::ControlPanel(nullptr));
                        std::shared_ptr<Gui::ControlPanel> p = std::dynamic_pointer_cast<Gui::ControlPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                    }
                    break;
                    case Gui::id::VIDEO_TAB:
                    {
                        gui.removeAllWidgets();
                        tgui::Panel::Ptr cust(new Gui::VideoPanel());
                        std::shared_ptr<Gui::VideoPanel> p = std::dynamic_pointer_cast<Gui::VideoPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                    }
                    break;
                    case Gui::id::SOUND_TAB:
                    {
                        gui.removeAllWidgets();
                        tgui::Panel::Ptr cust(new Gui::SoundPanel(nullptr));
                        std::shared_ptr<Gui::SoundPanel> p = std::dynamic_pointer_cast<Gui::SoundPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                    }
                    break;
                    case Gui::id::NETWORK_TAB:
                    {
                        gui.removeAllWidgets();
                        tgui::Panel::Ptr cust(new Gui::NetworkPanel());
                        std::shared_ptr<Gui::NetworkPanel> p = std::dynamic_pointer_cast<Gui::NetworkPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                    }
                    break;
                    case Gui::id::DEV_TAB:
                    {
                        gui.removeAllWidgets();
                        tgui::Panel::Ptr cust(new Gui::DevPanel());
                        std::shared_ptr<Gui::DevPanel> p = std::dynamic_pointer_cast<Gui::DevPanel>(cust);
                        p->init(debugDraw.GetFlags(), window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
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
                    }
                    break;
                    case Gui::id::HOST:
                    {
                        gui.removeAllWidgets();
                        tgui::Panel::Ptr cust(new Gui::HostPanel());
                        std::shared_ptr<Gui::HostPanel> p = std::dynamic_pointer_cast<Gui::HostPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                    }
                    break;
                    case Gui::id::CONNECT:
                    {
                        gui.removeAllWidgets();
                        tgui::Panel::Ptr cust(new Gui::ConnectPanel());
                        std::shared_ptr<Gui::ConnectPanel> p = std::dynamic_pointer_cast<Gui::ConnectPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");

                    }
                    break;
                    case Gui::id::CREDITS:
                      engin.push<CreditsState>(frame, engin, window, debugDraw, gui);
                    break;
                    case Gui::id::BACK:
                    {
                        Game *game = static_cast<Game*>(&engin);
                        game->setPop(true);
                    } 
                    return;
                }
            }
        }
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
                        GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                        prefMan.write("VelocityIterations", Settings::velocityIterations);
                    } 
                    break;
                    case Gui::id::POSITION_ITERATIONS:
                    {
                        Settings::positionIterations = int(temp->m_text[0] - '0'); 
                        GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                        prefMan.write("PositionIterations", Settings::positionIterations);
                    } 
                    break;
                    case Gui::id::FRAME_RATE:
                    {
                        Settings::frameRate = std::stoi(temp->m_text.c_str());
                        GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                        prefMan.write("FrameRate", Settings::frameRate);
                    } 
                    break;
                    case Gui::id::BALL_SPEED:
                    {
                        Settings::ballSpeed = std::stoi(temp->m_text.c_str());
                        GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                        prefMan.write("BallSpeed", Settings::ballSpeed);
                    } 
                    break;
                    case Gui::id::PADDLE_SPEED:
                    {
                        Settings::paddleSpeed = std::stoi(temp->m_text.c_str());
                        GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                        prefMan.write("PaddleSpeed", Settings::paddleSpeed);
                    } 
                    break;
                    case Gui::id::WALL_THICKNESS:
                    {
                        Settings::wallThickness = std::stoi(temp->m_text.c_str());
                        GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                        prefMan.write("WallThickness", Settings::wallThickness);
                    } 
                    break;
                    case Gui::id::BALL_RADIUS:
                    {
                        Settings::ballRadius = std::stoi(temp->m_text.c_str());
                        GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                        prefMan.write("BallRadius", Settings::ballRadius);
                    } 
                    break;
                    case Gui::id::PORT:
                    {
                        
                        Settings::port = std::stoi(temp->m_text.c_str());
                        GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                        prefMan.write("Port", Settings::port);
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
                            GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                            prefMan.write("b2aabb", Settings::b2aabb);
                        }
                        else
                        {
                            debugDraw.ClearFlags(b2Draw::e_aabbBit);
                            Settings::b2aabb = false;
                            GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                            prefMan.write("b2aabb", Settings::b2aabb);
                        }
                    }
                    break;
                    case Gui::DEBUG_SHAPE:
                    { 
                        if(temp->m_checked)
                        {
                            debugDraw.AppendFlags(b2Draw::e_shapeBit);
                            Settings::b2shapes = true;
                            GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                            prefMan.write("b2shapes", Settings::b2shapes);
                        }
                        else
                        {
                            debugDraw.ClearFlags(b2Draw::e_shapeBit);
                            Settings::b2shapes = false;
                            GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                            prefMan.write("b2shapes", Settings::b2shapes);
                        }
                    } 
                    break;
                    case Gui::DEBUG_MASS:
                    { 
                        if(temp->m_checked)
                        {
                            debugDraw.AppendFlags(b2Draw::e_centerOfMassBit);
                            Settings::b2centerOfMass = true;
                            GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                            prefMan.write("b2centerOfMass", Settings::b2centerOfMass);
                        }
                        else
                        {
                            debugDraw.ClearFlags(b2Draw::e_centerOfMassBit);
                            Settings::b2centerOfMass = false;
                            GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                            prefMan.write("b2centerOfMass", Settings::b2centerOfMass);
                        }
                    } 
                    break;
                    case Gui::DEBUG_JOINTS:
                    { 
                        if(temp->m_checked)
                        {
                            debugDraw.AppendFlags(b2Draw::e_jointBit);
                            Settings::b2joints = true;
                            GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                            prefMan.write("b2joints", Settings::b2joints);
                        }
                        else
                        {
                            debugDraw.ClearFlags(b2Draw::e_jointBit);
                            Settings::b2joints = false;
                            GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                            prefMan.write("b2joints", Settings::b2joints);
                        }
                    } 
                    break;
                    case Gui::DEBUG_PAIRS:
                    { 
                        if(temp->m_checked)
                        {
                            debugDraw.AppendFlags(b2Draw::e_pairBit);
                            Settings::b2pair = true;
                            GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                            prefMan.write("b2pair", Settings::b2pair);
                        }
                        else
                        {
                            debugDraw.ClearFlags(b2Draw::e_pairBit);
                            Settings::b2pair = false;
                            GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                            prefMan.write("b2pair", Settings::b2pair);
                        }
                    } 
                    break;
                    case Gui::DEBUG_LOG:
                        BP_LOG_WARNING("Debug Log not implimented");
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
                        GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                        prefMan.write("SoundVolume", Settings::soundVolume);
                    } 
                    break;
                    case Gui::id::MUSIC:
			        { 
                        ResourceManager::getMusic().setVolume(Settings::musicVolume);
                        GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                        prefMan.write("MusicVolume", Settings::musicVolume);
                    } 
                    break;
                };

            }
        }
        break;
        case EventId::PLAY_MUSIC:
        {
            std::shared_ptr<GU::Evt::OnPlayMusic> temp = std::dynamic_pointer_cast<GU::Evt::OnPlayMusic>(event);
            if(temp)
            {
                //Load music
                if(ResourceManager::loadMusic(temp->m_musicFile))
                    ResourceManager::getMusic().play();
		        else
                    ResourceManager::getMusic().stop();

            }
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
                        GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                        prefMan.write("Theme", Settings::currentTheme);
                        gui.removeAllWidgets();
                        tgui::Panel::Ptr cust(new Gui::VideoPanel());
                        std::shared_ptr<Gui::VideoPanel> p = std::dynamic_pointer_cast<Gui::VideoPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                    }
                    break;
                    case Gui::id::BACKGROUND:
                    {
                        switch(temp->m_index)
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
                    } 
                    break;
                    case Gui::id::MUSIC_COMBO:
                    {
                        ResourceManager::loadMusic(Settings::songList[temp->m_index]);
                        ResourceManager::getMusic().play();
                        Settings::currentSong = temp->m_index;
                        GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                        prefMan.write("Music", Settings::currentSong);
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
