#ifndef OBJECTBASE_H
#define OBJECTBASE_H
/**********************************************************//**
*   @author Wayne J Larson Jr.
*   @date   1/13/18
*   @brief  The base class for all objects in the game
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

//Box2D includes
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>


//SFML includes
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


//User defined includes
#include "Box2D/Box2DFunctions.h"

#include "Macros.h"

template <class SFShape>
class ObjectBase: public sf::Drawable
{
    public:
        /**********************************************************//**
        *   @brief  Constructor
        *   @param  [in] newWorld is a pointer to the Box2D world object
        *           where the game object exists.
        **************************************************************/
        ObjectBase(std::shared_ptr<b2World> newWorld);


        /**********************************************************//**
        *
        **************************************************************/
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        virtual void update() = 0;
        sf::Vector2f getPosition() const;
        void setPosition(const sf::Vector2f &newPosition);
        void setColor(const sf::Color &newColor);
        virtual ~ObjectBase();
    protected:
        b2Body *body = nullptr;
        SFShape shape;
        std::shared_ptr<b2World> world;
};

template <class SFShape>
void ObjectBase<SFShape>::setColor(const sf::Color &newColor)
{
    shape.setFillColor(newColor);
}

template <class SFShape>
sf::Vector2f ObjectBase<SFShape>::getPosition() const
{
    return toPixles(body->GetPosition());
}

template <class SFShape>
void ObjectBase<SFShape>::setPosition(const sf::Vector2f &newPosition)
{
    body->SetTransform(toMeters(newPosition), body->GetAngle());
}

template <class SFShape>
ObjectBase<SFShape>::ObjectBase(std::shared_ptr<b2World> newWorld): world(newWorld)
{
    //ctor
}

template <class SFShape>
void ObjectBase<SFShape>::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    UNUSED(states);
    target.draw(shape);
}

template <class SFShape>
ObjectBase<SFShape>::~ObjectBase()
{
    //dtor
    if(body->GetUserData())
    {
        int * temp = static_cast<int*>(body->GetUserData());
        delete temp;
    }

    world->DestroyBody(body);
}

#endif // OBJECTBASE_H
