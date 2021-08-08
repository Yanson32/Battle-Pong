#ifndef PADDLE_STOP_H
#define PADDLE_STOP_H
#include "Objects/ObjectBase.h"

class PaddleStop: public ObjectBase<sf::ConvexShape>
{
    public:
        PaddleStop(std::shared_ptr<b2World> newWorld, const std::array<sf::Vector2f, 4> &vert);
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        virtual void update() override;
        virtual ~PaddleStop();
};
#endif
