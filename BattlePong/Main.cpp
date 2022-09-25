/*************************************************************************
*                           COPYRIGHT NOTICE
* Battle Pong is a clone of the classic pong game.
* Copyright (C) 2017 Wayne J Larson Jr. 
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 3 as 
* published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
***************************************************************************/

#include "States/IntroState.h"
#include "Events/Events.h"
//#include <Box2D/Box2D.h>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "Game.h"
#include "Events/Events.h"

#include <SFML/Audio/Music.hpp>

#include "Resources/ResourceManager.h"
#include <boost/program_options.hpp>

#include <sstream>
#include <time.h>

#ifndef MAJOR_VERSION
    #define MAJOR_VERSION 1
#endif // MAJOR_VERSION

#include "config.h"
#include <GameUtilities/Core/String.h>
#include <GameUtilities/Engin/Frame.h>

#include "Settings.h"
#include "Objects/PongFrame.h"
#include "Box2D/DebugDraw.h"
#include <thread>

#include "SFMLFunctions.h"
#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <filesystem>
#include "Resources/ResourceManager.h"
#include <GameUtilities/Core/PreferencesManager.h>
#include <algorithm>

int main(int argc, char* argv[])
{
    //Retrieving the public ip address can take a while, especially if there is no internet connection.
    //So we do it in a thread.
    std::thread ipThread([&](){Settings::publicIp = sf::IpAddress::getPublicAddress().toString();});
    ipThread.detach();

    //Enable random numbers
    srand (time(NULL));

    //Create the games window
    sf::RenderWindow window(sf::VideoMode(Settings::dimensions.x, Settings::dimensions.y),Settings::title);

    //Setup the path to resource folder for the resource management system
    if(!std::filesystem::exists(ResourceManager::getPath()))
        ResourceManager::setPath(Settings::RESOURCE_INSTALL_DIR);
   
    //Set the log file path 
    Settings::logFile = ResourceManager::getPath().string();
    if(Settings::logFile.back() != '/')
        Settings::logFile += "/Log.txt";

    //Set the path to the preferences file
    Settings::preferencesFile = ResourceManager::getPath().string();
    if(Settings::preferencesFile.back() != '/')
     Settings::preferencesFile  += "/preferences.txt";

    GU::Core::PreferencesManager prefMan(Settings::preferencesFile);

    //Load game settings
    Settings::time = prefMan.read("ResetTime", Settings::time.toAnsiString()).toStdString();
    Settings::ai = prefMan.read("Difficulty", Settings::ai.toAnsiString()).toStdString();
    Settings::frameRate = prefMan.read("FrameRate", Settings::frameRate);
    Settings::ballSpeed = prefMan.read("BallSpeed", Settings::ballSpeed);
    Settings::paddleSpeed = prefMan.read("PaddleSpeed", Settings::paddleSpeed);
    Settings::wallThickness = prefMan.read("WallThickness", Settings::wallThickness);
    Settings::ballRadius = prefMan.read("BallRadius", Settings::ballRadius);

    //Load keyboard preferences
    Settings::playerControlUp = prefMan.read("PlayerControlUp", Settings::playerControlUp);
    Settings::playerControlDown = prefMan.read("PlayerControlDown", Settings::playerControlDown);
    Settings::playerControlLeft = prefMan.read("PlayerControlLeft", Settings::playerControlLeft);
    Settings::playerControlRight = prefMan.read("PlayerControlRight", Settings::playerControlRight);
    Settings::playerControlMenu = prefMan.read("PlayerControlMenu", Settings::playerControlMenu);
    Settings::playerControlNext = prefMan.read("PlayerControlNext", Settings::playerControlNext);
    Settings::playerControlSelect = prefMan.read("PlayerControlSelect", Settings::playerControlSelect);

    //Load joystick preferences
    Settings::playerJoystickControlMenu = prefMan.read("PlayerJoystickControlMenu", Settings::playerJoystickControlMenu);
    Settings::playerJoystickControlNext = prefMan.read("PlayerJoystickControlNext", Settings::playerJoystickControlNext);
    Settings::playerJoystickControlSelect = prefMan.read("PlayerJoystickControlSelect", Settings::playerJoystickControlSelect);

    //Load Box2D Settings
    Settings::b2aabb = prefMan.read("b2aabb", Settings::b2aabb);
    Settings::b2shapes = prefMan.read("b2shapes", Settings::b2shapes);
    Settings::b2centerOfMass = prefMan.read("b2centerOfMass", Settings::b2centerOfMass);
    Settings::b2joints = prefMan.read("b2joints", Settings::b2joints);
    Settings::b2pair = prefMan.read("b2pair", Settings::b2pair);
    Settings::velocityIterations = prefMan.read("VelocityIterations", Settings::velocityIterations);
    Settings::positionIterations = prefMan.read("PositionIterations", Settings::positionIterations);
    
    //Sound settings
    Settings::musicVolume = prefMan.read("MusicVolume", Settings::musicVolume);
    Settings::soundVolume = prefMan.read("SoundVolume", Settings::soundVolume);
    //Settings::currentSong = prefMan.read("Music", Settings::currentSong.toAnsiString());
    
    //Load log settings
    Settings::logSeverity = prefMan.read("LogSeverity", Settings::logSeverity);

    //Load tgui theme
    ResourceManager::loadTheme(Settings::theme);

    //Set the application icon
    sf::Image icon;
    icon.loadFromFile(ResourceManager::getPath().string() + "/Icons/BattlePong.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    //Create tgui object
    tgui::Gui gui;
    gui.setTarget(window);

    //Create the games frame
    std::shared_ptr<PongFrame> frame(new PongFrame(window.getView().getSize()));

    //Set the debug draw class
    DebugDraw debugDraw(*frame->world.get());
    frame->world->SetDebugDraw(&debugDraw);
    if(Settings::b2aabb)
      debugDraw.AppendFlags(b2Draw::e_aabbBit);
    if(Settings::b2shapes)
      debugDraw.AppendFlags(b2Draw::e_shapeBit);
    if(Settings::b2centerOfMass)
      debugDraw.AppendFlags(b2Draw::e_centerOfMassBit);
    if(Settings::b2joints)
      debugDraw.AppendFlags(b2Draw::e_jointBit);
    if(Settings::b2pair)
      debugDraw.AppendFlags(b2Draw::e_pairBit);

    //Handle program options
    std::stringstream ss;
    ss << MAJOR_VERSION << " " << ".0.0.0";

    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("version", MAJOR_VERSION + ".0.0.0")
        ("help", "produce help message");


    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).run(), vm);
    boost::program_options::notify(vm);


    if (vm.count("help"))
    {
        std::cout << desc << "\n";
        return 1;
    }

    //Create game engin
    Game engin;

    //Create first GameState instance
    engin.push<IntroState>(frame, engin, window, debugDraw, gui);

    //Start the music
    EventManager::inst().post<GU::Evt::PlayMusic>("Zombies");

    //Create clock for game engin
    sf::Clock timer;
    const sf::Time deltaTime = sf::seconds(1.0f / Settings::frameRate);
    sf::Time accumulator = sf::seconds(0);

    try
    {
        while (engin.isRunning())
        {
            accumulator += timer.restart();

	          //Handle any events
	          engin.handleEvents(deltaTime.asSeconds(), frame);
              
              //If we need to pop a state off the stack we need to do it
              //When the state is not in use or we will destroy the stack.
              if(engin.getPop())
              {
                engin.setPop(false);
                engin.pop(frame);
              }

	          //Update the game logic
	          while(accumulator.asSeconds() >= deltaTime.asSeconds())
            {
                engin.update(deltaTime.asSeconds(), frame);
                accumulator -= deltaTime;
            }

	          //Draw a frame
	          engin.draw(deltaTime.asSeconds(), frame);
        }
    }
    catch(...)
    {

    }

}
