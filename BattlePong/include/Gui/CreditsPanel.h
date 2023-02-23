#ifndef BP_CREDITS_PANEL
#define BP_CREDITS_PANEL
/**********************************************************************//**
*   @author Wayne J Larson Jr.
*   @date   2/22/2023
*   @file   CreditsPanel.h
**************************************************************************/

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
#include "Gui/CustomPanel.h"
#include <TGUI/TGUI.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace Gui
{
    /**********************************************************************//**
    *   @class  CreditsPanel 
    *   @brief  This class displays the credits for the game 
    **************************************************************************/
    class CreditsPanel: public sf::Drawable
    {
        public:
            /**********************************************************************//**
            *   @brief  Constructor 
            **************************************************************************/
            CreditsPanel();
            

            /**********************************************************************//**
            *   @brief  This method sets the position of the panel.
            *   @param  width is the new position on the x axis.
            *   @param  height is the new position on the y axis. 
            **************************************************************************/
            void setPosition(const float &width, const float &height);
            

            /**********************************************************************//**
            *   @brief  This method sets the size of the panel.
            *   @param  width is the new width of the panel.
            *   @param  height is the new height of the panel.
            **************************************************************************/
            void setSize(const float &width, const float &height);
            

            /**********************************************************************//**
            *   @brief  This method adds a credit to the panel. The credits are cycled
            *           through one at a time. 
            *   @param  texture is a credit to someone who contributed to the game. 
            **************************************************************************/
            void add(sf::Texture &texture);
            

            /**********************************************************************//**
            *   @brief  This method sets the background color of the panel. 
            *   @param  color is the new background color of the panel 
            **************************************************************************/
            void setBackgroundColor(const sf::Color &color);
            

            /**********************************************************************//**
            *   @brief  This method sets the origin of the panel.
            *   @param  width is the position of the origin on the x axis relative
            *           to the upper left corner of the panel.
            *   @param  height is the position of the origin on the y axis relative
            *           to the upper left corner of the panel.
            **************************************************************************/
            void setOrigin(const float &width, const float &height);
            

            /**********************************************************************//**
            *   @brief  This method draws the panel to the screen. 
            *   @param  target is the window the panel will be drawn to. 
            *   @param  states is the properties used when drawing the panel.  
            **************************************************************************/
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            

            /**********************************************************************//**
            *   @brief  This method will cause the panel to display the next credit. 
            **************************************************************************/
            void next();
            

            /**********************************************************************//**
            *   @brief  This method will cause the panel to display the previous credit. 
            **************************************************************************/
            void prev();
            

            /**********************************************************************//**
            *   @brief  Destructor 
            **************************************************************************/
            virtual ~CreditsPanel();        
        private:
            sf::RectangleShape m_background;                //! This RectangleShape is used to display a backdrop for the text.
            std::vector<sf::RectangleShape> m_textures;     //! This vector stores textures of credits.
            std::size_t m_currentTexture = 0;               //! The index of the current credit.
    };
}

#endif

