#ifndef PADDLE_H
#define PADDLE_H

#include "ObjectBase.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "Input.h"
#include <memory>

class Ball;
class b2Body;
class Paddle: public ObjectBase<sf::ConvexShape>
{
    public:
        Paddle(b2World &world, const std::array<sf::Vector2f, 4> vert);
        void setPosition(const sf::Vector2f &position);
        sf::Vector2f getPosition() const;
        void handleInput(const Ball &ball);
        void setInput(std::unique_ptr<Input> newInput);
        void move(const sf::Vector2f &direction);
        virtual void update();
        ~Paddle();
    private:
        std::unique_ptr<Input> input;
        b2Body *jointBody = nullptr;
        b2PrismaticJoint *prisJoint;
};

#endif
