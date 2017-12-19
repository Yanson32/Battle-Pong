#ifndef PONG_WALL_H
#define PONG_WALL_H
#include <Box2D/Box2D.h>
#include "ObjectBase.h"
#include <SFML/System/Vector2.hpp>
#include <array>

class Wall: public ObjectBase
{
    public:
        Wall(b2World &world, const std::array<sf::Vector2f, 4> vert);
        void setPosition(const sf::Vector2f &position);
        void setSize(const sf::Vector2f &size);
        void update();
        virtual ~Wall();
    protected:
    private:
};

#endif // WALL_H
