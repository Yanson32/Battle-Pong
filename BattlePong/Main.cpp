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

#include "Engin/States/IntroState.h"
#include "Events/Events.h"
//#include <Box2D/Box2D.h>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "Engin/Game.h"
#include "Events/Events.h"
#include "Events/EventManager.h"
#include "Gui/GuiId.h"

#include <SFML/Audio/Music.hpp>

#include "Resources/ResourceManager.h"

#include <sstream>
#include <time.h>

#ifndef MAJOR_VERSION
    #define MAJOR_VERSION 1
#endif // MAJOR_VERSION

#include "config.h"
#include <GameUtilities/Core/String.h>
#include <GameUtilities/Engin/Frame.h>
#include <GameUtilities/Core/Paths.h>
#include <GameUtilities/Event/Events/Widget/OnItemSelected.h>

#include "Settings.h"
#include "Engin/PongFrame.h"
#include "Box2D/DebugDraw.h"
#include <thread>

#include "SFMLFunctions.h"
#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <filesystem>
#include "Resources/ResourceManager.h"
#include "Resources/Images/Icons/BattlePongPng.h"
#include <algorithm>
#include <filesystem>
#include "ErrorCodes.h"
#include "Arguments.h"
#include "WriteSettings.h"
#include "WriteLog.h"
#include "Log.h"

int main(int argc, char* argv[])
{
    programArguments(argc, argv);

 
    BP_LOG_MESSAGE("GAME_CONFIG_DIR = " + Settings::GAME_CONFIG_DIR);   
    Settings::publicIp.setString("0.0.0.0");
 
    //Retrieving the public ip address can take a while, especially if there is no internet connection.
    //So we do it in a thread.
    std::thread ipThread([&](){Settings::publicIp.setString(sf::IpAddress::getPublicAddress().toString());});
    ipThread.detach();

    //Enable random numbers
    srand (time(NULL));

    //Create the games window
    sf::RenderWindow window(sf::VideoMode(Settings::dimensions.x, Settings::dimensions.y),Settings::title);

    //Set game icon
    sf::Image gameIcon;
    if(!gameIcon.loadFromFile(Settings::GAME_CONFIG_DIR + "/Icons/BattlePong.png"))
    {
        BP_LOG_ERROR("Unable to load game icon");
    }
    window.setIcon(gameIcon.getSize().x, gameIcon.getSize().y, gameIcon.getPixelsPtr());


    
    //Setup the path to resource folder for the resource management system
    if(!std::filesystem::exists(ResourceManager::getPath()))
        ResourceManager::setPath(Settings::GAME_CONFIG_DIR);

    //Set the log file path 
    Settings::logFile = Settings::GAME_CONFIG_DIR;
    if(Settings::logFile.back() != '/')
        Settings::logFile += "/Log.txt";

    //Set the path to the preferences file
    Settings::preferencesFile = Settings::GAME_CONFIG_DIR;
    if(Settings::preferencesFile.back() != '/')
        Settings::preferencesFile  += "/preferences.txt";


    //Load tgui theme
    ResourceManager::loadTheme(Settings::currentTheme);

    ResourceManager::loadTexture(textureId::ICON, BattlePong_png, BattlePong_png_len);

    //Set the application icon
    sf::Image icon = ResourceManager::get(textureId::ICON).copyToImage();
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

    //Create game engin
    Game engin;
    
    //WriteLog will write all logs to the log file when exiting the program
    WriteLog writeLog(engin);
    
    //Write settings on game close
    WriteSettings write;

    //Create first GameState instance
    engin.push<IntroState>(frame, engin, window, debugDraw, gui);

    //Set the song 
    EventManager::inst().post<GU::Evt::OnItemSelected>(nullptr, Gui::id::MUSIC_COMBO, Settings::currentSong);

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
                engin.sync(frame);
                accumulator -= deltaTime;
            }

	          //Draw a frame
	          engin.draw(deltaTime.asSeconds(), frame);
        }
    }
    catch(...)
    {

    }

    window.close();
    return ErrorCode::SUCESS;
}
