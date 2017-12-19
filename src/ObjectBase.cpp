#include "ObjectBase.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

ObjectBase::ObjectBase()
{
    //ctor
}

void ObjectBase::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape);
}

ObjectBase::~ObjectBase()
{
    //dtor
}
