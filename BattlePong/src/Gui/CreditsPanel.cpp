/**********************************************************************//**
*   @author Wayne J Larson Jr.
*   @date   2/22/2023
*   @file   CreditsPanel.cpp
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
#include <Gui/CreditsPanel.h>
#include <SFML/Graphics/Color.hpp>

namespace Gui
{

    /**********************************************************************//**
    *   @brief  Constructor 
    **************************************************************************/
    CreditsPanel::CreditsPanel()
    {
       m_background.setSize({200.0f, 200.0f});
    }

    
    /**********************************************************************//**
    *   @brief  This method sets the position of the panel.
    *   @param  width is the new position on the x axis.
    *   @param  height is the new position on the y axis. 
    **************************************************************************/
    void CreditsPanel::setPosition(const float &width, const float &height)
    {
        m_background.setPosition({width, height});
        for(std::size_t i = 0; i < m_textures.size(); ++i)
        {
            m_textures[i].setPosition(width, height);
        }
    }

    
    /**********************************************************************//**
    *   @brief  This method sets the size of the panel.
    *   @param  width is the new width of the panel.
    *   @param  height is the new height of the panel.
    **************************************************************************/
    void CreditsPanel::setSize(const float &width, const float &height)
    {
        m_background.setSize({width, height});
        for(std::size_t i = 0; i < m_textures.size(); ++i)
        {
            m_textures[i].setSize({width, height});
        }
    }
    
    
    /**********************************************************************//**
    *   @brief  This method adds a credit to the panel. The credits are cycled
    *           through one at a time. 
    *   @param  texture is a credit to someone who contributed to the game. 
    **************************************************************************/
    void CreditsPanel::add(sf::Texture &texture)
    {
        sf::RectangleShape shape;
        shape.setTexture(&texture);
        shape.setSize(m_background.getSize());
        shape.setOrigin(m_background.getOrigin());
        shape.setPosition(m_background.getPosition());
        m_textures.push_back(shape);
    }

    
    /**********************************************************************//**
    *   @brief  This method sets the background color of the panel. 
    *   @param  color is the new background color of the panel 
    **************************************************************************/
    void CreditsPanel::setBackgroundColor(const sf::Color &color)
    {
       m_background.setFillColor(color);
    }
    

    /**********************************************************************//**
    *   @brief  This method sets the origin of the panel.
    *   @param  width is the position of the origin on the x axis relative
    *           to the upper left corner of the panel.
    *   @param  height is the position of the origin on the y axis relative
    *           to the upper left corner of the panel.
    **************************************************************************/
    void CreditsPanel::setOrigin(const float &width, const float &height)
    {
        m_background.setOrigin(width, height);
        for(std::size_t i = 0; i < m_textures.size(); ++i)
        {
            m_textures[i].setOrigin(width, height);
        }
    }
    

    /**********************************************************************//**
    *   @brief  This method draws the panel to the screen. 
    *   @param  target is the window the panel will be drawn to. 
    *   @param  states is the properties used when drawing the panel.  
    **************************************************************************/
    void CreditsPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_background, states);
        target.draw(m_textures[m_currentTexture], states);
    }


    /**********************************************************************//**
    *   @brief  This method will cause the panel to display the next credit. 
    **************************************************************************/
    void CreditsPanel::next()
    {
        m_currentTexture += 1;
        if(m_currentTexture >= m_textures.size())
            m_currentTexture = 0;
    }

    
    /**********************************************************************//**
    *   @brief  This method will cause the panel to display the previous credit. 
    **************************************************************************/
    void CreditsPanel::prev()
    {
        if(m_currentTexture == 0)
        {
            m_currentTexture = m_textures.size() - 1;
        }
        else
        {
            m_currentTexture -= 1;
        }

    }


    /**********************************************************************//**
    *   @brief  Destructor 
    **************************************************************************/
    CreditsPanel::~CreditsPanel()
    {

    }

}
