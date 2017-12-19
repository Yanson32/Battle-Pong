#ifndef PONG_BALL_H
#define PONG_BALL_H
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/CircleShape.hpp>
class b2Body;
class b2World;
class Ball: public sf::Drawable
{
    public:
        Ball(b2World &world);
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        void update();
        virtual ~Ball();
        b2Body *body = nullptr;
        sf::CircleShape circle;
};

#endif // BALL_H
