#ifndef PONG_BALL_H
#define PONG_BALL_H
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
        Ball(b2World &world);
        void update();
        virtual ~Ball();
};

#endif // BALL_H
