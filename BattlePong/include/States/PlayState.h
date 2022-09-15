#ifndef PONG_PLAYSTATE_H
#define PONG_PLAYSTATE_H

/************************************************************//**
*   @author Wayne J Larson Jr
*   @date   12/24/17
*   @brief  PlayState This state is where the game logic is
*           executed.
****************************************************************/

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
#include "States/StateBase.h"
#include "Objects/Ball.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Clock.hpp>

#include <memory>

#include "Box2D/DebugDraw.h"
#include <TGUI/TGUI.hpp>

#include <GameUtilities/Engin/Frame.h>

class PlayState: public StateBase
{
    public:
        /****************************************************************//**
        *   @brief  Constructor
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        PlayState(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow, DebugDraw &debugDraw, tgui::Gui &newGui, const StateId newId = StateId::PLAY_STATE);

        void sfEvent(GU::Engin::Engin& engin, const sf::Event &event, std::shared_ptr<GU::Engin::Frame> frame);
        void handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event, std::shared_ptr<GU::Engin::Frame> frame);
        virtual void init(std::shared_ptr<GU::Engin::Frame> frame) override;
        virtual void clean(std::shared_ptr<GU::Engin::Frame> frame) override;

        /****************************************************************//**
        *   @brief  This method handles input such as user input and events.
        *           This should be called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        void handleEvents(GU::Engin::Engin& newEngin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame) override;


        /****************************************************************//**
        *   @brief  This method updates the game logic. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        void update(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame) override;


        /****************************************************************//**
        *   @brief  This method draws the current frame. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        void draw(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame) override;


        /****************************************************************//**
        *   @brief  Destructor
        ********************************************************************/
        ~PlayState();
    private:
};
#endif
