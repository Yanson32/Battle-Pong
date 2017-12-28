#ifndef PONG_BALL_H
#define PONG_BALL_H
/**********************************************************//**
*   @author Wayne J Larson Jr.
*   @date   12/25/17
*   @brief  This class represents a ball.
**************************************************************/


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
        Ball(b2World &world, const unsigned radius = 8);


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
};

#endif // BALL_H
