#ifndef BOX2DFUNCTIONS_H
#define BOX2DFUNCTIONS_H
/**********************************************************//**
*   @author Wayne J Larson Jr.
*   @date   12/25/17
*   @brief  This file defines free standing functions to be
*           used with Box2D.
**************************************************************/

#include <Box2D/Box2D.h>
#include <SFML/System/Vector2.hpp>


/**********************************************************//**
*   @brief  Convert pixles to Box2D meters.
*   @param  pixles a distance in pixles.
**************************************************************/
float32 toMeters(const float32 &pixles);


/**********************************************************//**
*   @brief  Convert meters to pixles
*   @param  meters distance in Box2D meters
**************************************************************/
float toPixles(const float &meters);


/**********************************************************//**
*   @brief  Convert SFML Vector2f in pixles to Box2D
*           b2Vec2 in Box2D meters
*   @param  pixles Coordinate in meters.
**************************************************************/
b2Vec2 toMeters(const sf::Vector2f &pixles);


/**********************************************************//**
*   @brief  Convert Box2D b2Vec2 coordinate in meters, to SFML
*           coordinate in pixles.
*   @param  pixles Coordinate in pixles.
**************************************************************/
sf::Vector2f toPixles(const b2Vec2 &meters);
#endif
