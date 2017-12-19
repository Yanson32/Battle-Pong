#ifndef OBJECTBASE_H
#define OBJECTBASE_H
#include <Box2D/Box2D.h>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

class ObjectBase: public sf::Drawable
{
    public:
        ObjectBase();
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        virtual void update() = 0;
        virtual ~ObjectBase();
    protected:
        b2Body *body = nullptr;
        sf::ConvexShape shape;
};

#endif // OBJECTBASE_H
