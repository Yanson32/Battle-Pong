#ifndef STATEBASE_H
#define STATEBASE_H

/************************************************************//**
*   @author Wayne J Larson Jr
*   @date   12/24/17
*   @brief  StateBase This is the parent class for all states.
****************************************************************/

/************************************************************************
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
#include <GameUtilities/Engin/GameState.h>
#include <GameUtilities/Engin/Frame.h>

#include <GameUtilities/Event/EventHandler.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>

#include <Box2D/Box2D.h>
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

#include "Box2D/DebugDraw.h"
#include "Box2D/ContactListener.h"

#include "Objects/Goal.h"
#include "Objects/PaddleStop.h"

#include "Gui/PaddleHud.h"
#include "States/StateId.h"

#include <memory>
#include <TGUI/TGUI.hpp>

#include "Objects/PongFrame.h"

class Wall;
class Paddle;
class Ball;
namespace GU
{
    namespace Engin
    {
        class Engin;
    }
}
class StateBase: public GU::Engin::GameState, public GU::Evt::EventHandler
{
    public:
        /****************************************************************//**
        *   @brief  Constructor
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        StateBase(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow, DebugDraw &newDebugDraw, tgui::Gui &newGui, const StateId newState);


        virtual void init(std::shared_ptr<GU::Engin::Frame> frame) override;
        virtual void clean(std::shared_ptr<GU::Engin::Frame> frame) override = 0;

        /****************************************************************//**
        *   @brief  This method handles input such as user input and events.
        *           This should be called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void handleEvents(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame) override = 0;


        /****************************************************************//**
        *   @brief  This method updates the game logic. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void update(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame) override;


        /****************************************************************//**
        *   @brief  This method draws the current frame. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void draw(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame) override;



        void sfEvent(GU::Engin::Engin& engin, const sf::Event &event, std::shared_ptr<GU::Engin::Frame> frame);


        void handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event, std::shared_ptr<GU::Engin::Frame> frame) override;


        /****************************************************************//**
        *   @brief  This method allows the system to pause the game.
        *           When system pause is in effect regular pause won't
        *           work.
        *   @param  newSysPaus true if the system is pausing the game and,
        *           false otherwise.
        ********************************************************************/
        void systemPause(const bool newSysPause);


        /****************************************************************//**
        *   @brief  Checks to see if system pause is in effect.
        *   @return boolean true if system pause is in effect and false
        *           otherwise.
        ********************************************************************/
        bool isSystemPaused() const;

        void reset(std::shared_ptr<PongFrame> frame);
        /****************************************************************//**
        *   @brief  Destructor
        ********************************************************************/
        virtual ~StateBase();
    protected:
        void centerText();
        bool isBallOnScreen(std::shared_ptr<PongFrame> frame);
        GU::Engin::Engin &engin;                        ///The Main game engin
        sf::RenderWindow &window;
        DebugDraw &debugDraw;
        tgui::Gui &gui;                           ///The Main TGUI object
        StateId state;
        static sf::Sound sound;
        static ContactListener contactListener;         ///Subclass of Box2D b2ContactListener used to detect Box2D collisions
        static sf::Text userMessage;                    ///Text displayed in the center of the screen
        static sf::Clock messageClock;                  ///This clock object is used to time the beginning message "Ready!, 3, 2, 1, Go!
        static sf::Clock roundClock;                    ///This clock tracks the time for each round and resets the game when the time has expired
        bool sysPause;                                  ///True when the system is paused and false otherwise
        static sf::RectangleShape backgroundRect;

};

#endif // STATEBASE_H
