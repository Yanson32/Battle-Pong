#ifndef PONG_BALL_H
#define PONG_BALL_H
/**********************************************************//**
*   @author Wayne J Larson Jr.
*   @date   12/25/17
*   @brief  This class represents a ball.
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

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "ObjectBase.h"


class b2Body;
class b2World;



class Ball: public ObjectBase<sf::CircleShape>
{
    public:
        /**********************************************************//**
        *   @brief  Constructor
        *   @param  world a referance to the Box2D world object where
        *           the ball will exist.
        *   @param  radius the radius of the ball object
        **************************************************************/
        Ball(std::shared_ptr<b2World> world, const unsigned radius = 8);


        /**********************************************************//**
        *   @brief  This method executes the per frame logic.
        **************************************************************/
        void update();


        /**********************************************************//**
        *   @brief  Set the velocity of the ball object.
        *   @param  newVelocity the new velocity of the ball object
        *           in pixles.
        **************************************************************/
        void setVelocity(const sf::Vector2f &newVelocity);


        /**********************************************************//**
        *   @brief  Destructor
        **************************************************************/
        virtual ~Ball();
    private:
};

#endif // BALL_H
