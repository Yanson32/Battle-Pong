#ifndef SETTINGS_H
#define SETTINGS_H
/**********************************************************//**
*   @author Wayne J Larson Jr.
*   @date   12/25/17
*   @brief  The MusicSettings constructor
**************************************************************/

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

#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <TGUI/TGUI.hpp>
#include <SFML/Network.hpp>
#include "Events/EventId.h"
#include "States/StateId.h"
#include <string>

namespace Settings
{
    //Game settings
    extern sf::String time;
    extern sf::String ai;
    extern int wallThickness;
    extern StateId stateId;
    extern int ballRadius;  
    extern int ballSpeed;
    extern int paddleSpeed;

    //Paddle 1 settigns
    extern std::string p1Input;
    extern std::string p1Name;
    extern int p1Score;

    //Paddle 2 settigns
    extern std::string p2Input;
    extern std::string p2Name;
    extern int p2Score;

    //music settings
    extern int musicVolume;
    extern int soundVolume;
    extern sf::String currentSong;

    //Button Settings
    extern sf::Vector2f bSize;
    extern sf::Vector2f bPosition;

    //Window settings
    extern sf::String title;
    extern sf::Vector2f dimensions;


    //Player controls
    extern std::string playerControlUp;
    extern std::string playerControlDown;
    extern std::string playerControlLeft;
    extern std::string playerControlRight;
    extern std::string playerControlMenu;
    extern std::string playerControlNext;
    extern std::string playerControlSelect;

    //Joystick buttons
    extern std::string playerJoystickControlMenu;
    extern std::string playerJoystickControlNext;
    extern std::string playerJoystickControlSelect;


    //Network
    extern sf::TcpSocket socket;
    extern sf::TcpListener listener;
    extern bool connected;
    extern sf::String targetIp;
    extern sf::Time timeOut;
    extern int port;
    extern std::string publicIp;
    extern std::string localIp;

    //Theme settings
    extern std::string theme;
    extern std::string background;

    extern std::string preferencesFile;

    //Directories
    extern const std::string RESOURCE_INSTALL_DIR;

    extern int logSeverity;

    //Debug draw settings
    extern bool b2aabb;
    extern bool b2shapes;
    extern bool b2centerOfMass;
    extern bool b2joints;
    extern bool b2pair;
    
    extern int velocityIterations;
    extern int positionIterations;
    extern int frameRate;
    
}


#endif
