#ifndef BOX2DFUNCTIONS_H
#define BOX2DFUNCTIONS_H
#include <Box2D/Box2D.h>
#include <SFML/System/Vector2.hpp>


float32 toMeters(const float32 &meters);
float toPixles(const float &meters);
b2Vec2 toMeters(const sf::Vector2f &pixles);
sf::Vector2f toPixles(const b2Vec2 &meters);
#endif
