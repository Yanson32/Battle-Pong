#ifndef OBJECTBASE_H
#define OBJECTBASE_H
#include <Box2D/Box2D.h>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Box2D/Box2DFunctions.h"

template <class SFShape>
class ObjectBase: public sf::Drawable
{
    public:
        ObjectBase();
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        virtual void update() = 0;
        sf::Vector2f getPosition() const;
        void setPosition(const sf::Vector2f &newPosition);
        void setColor(const sf::Color &newColor);
        virtual ~ObjectBase();
    protected:
        b2Body *body = nullptr;
        SFShape shape;
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
ObjectBase<SFShape>::ObjectBase()
{
    //ctor
}

template <class SFShape>
void ObjectBase<SFShape>::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape);
}

template <class SFShape>
ObjectBase<SFShape>::~ObjectBase()
{
    //dtor
}
#endif // OBJECTBASE_H
