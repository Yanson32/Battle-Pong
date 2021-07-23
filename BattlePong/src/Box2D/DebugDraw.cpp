#include "Box2D/DebugDraw.h"


//SFML includes
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>


//Box2D includes
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2World.h>


//STD includes
#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstddef> //std::size_t
#include <vector>

#include "Macros.h"

namespace
{
    const float PIE = 3.141592654f;
    const float TAU = 2 * PIE;

    /**********************************************************************************************
    *   Purpose:    This method converts a circle to points along the circumference of the circle.
    *   Input:      const b2Vec2& the center of the circle.
    *               float32 the radius of the circle.
    *               const unsigned the number of points around the circumference to be created.
    *   return:     std::vector<b2Vec2> a vector of points along the circumference.
    **********************************************************************************************/
    std::vector<b2Vec2> getPoints(const b2Vec2& center, float32 radius, const unsigned pointCount);


    /****************************************************************************************
    *   Purpose:    This converts a box2d color object to an SFML color object.
    *   Input:      const b2Color &color this parameter is a box2d color which will be
    *               converted to an SFML color.
    *               int alpha this parameter represents the alpha (opacity) of the color.
    *   Return:     sf::Color object which is created from the input parameters.
    ****************************************************************************************/
    sf::Color toSfColor(const b2Color &color, int alpha = 255);

}


    /***************************************************************************************************************//**
    *   @brief  This method is a constructor.
    *   @param  newWorld a reference to a Box2D world object which will
    *           be stored internally untill object deletion.
    *   @param  newPixelsPerMeter is used to convert between pixles and
    *           Box2D meters
    *   @param  circleScaling effects the number of points used to draw a circle
    *******************************************************************************************************************/
    DebugDraw::DebugDraw(b2World& newWorld, const float newPixelsPerMeter, const float circleScaling):
    pixelsPerMeter(newPixelsPerMeter),
    world(newWorld),
    m_circleScaling(circleScaling)
    {
        lines.setPrimitiveType(sf::Lines);
        triangles.setPrimitiveType(sf::Triangles);

//        e_shapeBit ( draw shapes )
//        e_jointBit ( draw joint connections
//        e_aabbBit ( draw axis aligned bounding boxes )
//        e_pairBit ( draw broad-phase pairs )
//        e_centerOfMassBit ( draw a marker at body CoM )

    }


    /*******************************************************************************************************************
    *   Purpose:    This method draws axis alligned bounding boxes.
    *   Input:      b2Vec2* vertices which is an array of verticies.
    *               int32 vertexCount the number of vertices in the vertices parameter.
    *               const b2Color which is the color the axis aligned bounding box should be drawn with
    *   pre:        This class must first be registered with a box2d world object.
    *               The e_aabbBit must be set.
    *******************************************************************************************************************/
    void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
    {
        for(int i = 0; i < vertexCount - 1; ++i)
        {
            DrawSegment(vertices[i], vertices[i + 1], color);
        }

        DrawSegment(vertices[vertexCount - 1], vertices[0], color);
    }


	/***************************************************************************************************************//**
	*   @brief  This method draws all shapes except circles.
	*   @param  vertices which is an array of verticies.
	*   @param  vertexCount the number of vertices in the vertices parameter.
	*   @param  color which is the color the axis aligned bounding box should be drawn with
	*   pre:    This class must first be registered with a box2d world object.
	*           The e_shapeBit must be set.
	*******************************************************************************************************************/
    void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
    {
        const sf::Color COLOR = toSfColor(color);

        for(int i = 0; i < vertexCount - 2; ++i)
        {

            sf::Vertex vertA;
            vertA.position = this->toPixels(vertices[i]);
            vertA.color = COLOR;
            triangles.append(vertA);

            sf::Vertex vertB;
            vertB.position = this->toPixels(vertices[i + 1]);
            vertB.color = COLOR;
            triangles.append(vertB);

            sf::Vertex vertC;
            vertC.position = this->toPixels(vertices[i + 2]);
            vertC.color = COLOR;
            triangles.append(vertC);
        }


        sf::Vertex vertA;
        vertA.position = this->toPixels(vertices[vertexCount - 2]);
        vertA.color = COLOR;

        sf::Vertex vertB;
        vertB.position = this->toPixels(vertices[vertexCount - 1]);
        vertB.color = COLOR;

        sf::Vertex vertC;
        vertC.position = this->toPixels(vertices[0]);
		vertC.color = COLOR;

        triangles.append(vertA);
        triangles.append(vertB);
        triangles.append(vertC);
    }


    /***************************************************************************************************************//**
    *   @brief  This method draws the outline of a circle.
    *   @param  const b2Vec2& center this parameter is the center of the circle.
    *   @param  radius this parameter is the radius of the circle.
    *   @param  color this parameter is the color that the circle will be drawn with
    *   Pre:    This class must first be registered with a box2d world object.
    *******************************************************************************************************************/
    void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
    {
        const unsigned      POINT_COUNT = ((toPixels(radius) * TAU) * m_circleScaling);
        std::vector<b2Vec2> points = getPoints(center, radius, POINT_COUNT);
        assert(points.size() != 0);

        for(std::size_t i = 0; i < points.size() - 1; ++i)
        {
            DrawSegment(points[i], points[i + 1], color);
        }

        DrawSegment(points[points.size() - 1], points[0], color);
    }


    /***************************************************************************************************************//**
    *   @brief  This method draws circle objects. The circle will be drawn as a circle filled with color.
    *   @param  center the center point of the circle to be drawn
    *   @param  radius this is the radius of the circle.
    *   @param  axis is a direction vector relative to the center of the circle. The axis is used
	* 			to draw a line from the center of the circle to the circumference to indicate thie circle's rotation.
    *   @param  color this is the color the circle will be drawn in.
    *   Pre:        This class must first be registered with a box2d world object.
    *               The e_shapeBit must be set.
    ********************************************************************************************************************/
    void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
    {
        
        UNUSED(axis);
        const unsigned POINT_COUNT = (unsigned) ((toPixels(radius) * TAU) * m_circleScaling);
        const sf::Color COLOR = toSfColor(color);


        //Draw the circle
        sf::Vector2f CENTER_POINT = this->toPixels(center);
        std::vector<b2Vec2> points = getPoints(center, radius, POINT_COUNT);

        assert(points.size() != 0);
        for(std::size_t i = 0; i < points.size() - 1; ++i)
        {

            sf::Vertex vertA;
            vertA.position = CENTER_POINT;
            vertA.color = COLOR;

            sf::Vertex vertB;
			vertB.position = this->toPixels(points[i]);
            vertB.color = COLOR;

            sf::Vertex vertC;
            vertC.position = this->toPixels(points[i + 1]);
            vertC.color = COLOR;

            triangles.append(vertA);
            triangles.append(vertB);
            triangles.append(vertC);
        }


        sf::Vertex vertA;
        vertA.position = CENTER_POINT;
        vertA.color = COLOR;

        sf::Vertex vertB;
        vertB.position = this->toPixels(points[points.size() - 1]);
        vertB.color = COLOR;

        sf::Vertex vertC;
        vertC.position = this->toPixels(points[0]);
        vertC.color = COLOR;

        triangles.append(vertA);
        triangles.append(vertB);
        triangles.append(vertC);
    }



    /*******************************************************************************************************************
    *   @brief  This method draws a line segment to the screen.
    *   @param  p1 this is the first point of the line segment.
    *   @param  p2 this is the second point of the line segment.
    *   @param  color this is a struct that defines the blue, green, red color values.
    *   Pre:        This class must first be registered with a box2d world object.
    *               The e_shapeBit must be set.
    *******************************************************************************************************************/
    void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
    {
        //Convert Box2D parameters to SFML
        const sf::Color     COLOR           = toSfColor(color);
        const sf::Vector2f  FIRST_POINT     = this->toPixels(p1);
        const sf::Vector2f  SECOND_POINT    = this->toPixels(p2);


        //Create two points
        sf::Vertex vertA;
        vertA.position      = FIRST_POINT;
        vertA.color         = COLOR;

        sf::Vertex vertB;
        vertB.position      = SECOND_POINT;
        vertB.color         = COLOR;

        //Add points to lines VertexArray
        lines.append(vertA);
        lines.append(vertB);
    }


    /***************************************************************************************************************//**
    *   @brief  This method draws a transform to the screen when the e_centerOfMassBit is set.
    *   @param  xf which is the transform to be drawn to the screen.
    *   Pre:    This class must first be registered with a box2d world object.
    *           The e_centerOfMassBit must be set or the function won't be called
    *******************************************************************************************************************/
    void DebugDraw::DrawTransform(const b2Transform& xf)
    {
        const float32 LENGTH            = 0.2f;
        const b2Vec2 CENTER_POINT       = (xf.p);
        const b2Vec2 HORIZONTAL_POINT   = (xf.p + (LENGTH * xf.q.GetXAxis()));
        const b2Vec2 VERTICAL_POINT     = (xf.p + (LENGTH * xf.q.GetYAxis()));


        //Draw transform
        DrawSegment(CENTER_POINT, HORIZONTAL_POINT, b2Color(0, 1, 0));
        DrawSegment(CENTER_POINT, VERTICAL_POINT, b2Color(1, 0, 0));
    }


    /***************************************************************************************************************//**
    *   @param  This method does per frame logic and must be called once per frame.
    *******************************************************************************************************************/
    void DebugDraw::update()
    {
        triangles.resize(0);
        lines.resize(0);
        world.DrawDebugData();
    }


    /*******************************************************************************************************************
    *   Purpose:    This method converts b2Vec2 in box2d meters to sf::Vector2f in pixles.
    *   Input:      const b2Vec2 the point in box2d meters.
    *   Return:     sf::Vector2f the point in pixles.
    *******************************************************************************************************************/
    sf::Vector2f DebugDraw::toPixels(const b2Vec2 &vec)
    {
        sf::Vector2f temp;
        temp.x = this->toPixels(vec.x);
        temp.y = this->toPixels(vec.y);
        return temp;
    }


    /*******************************************************************************************************************
    *   Purpose:    This method converts float32 in box2d meters to float32 in pixles.
    *   Input:      const float32 in meters
    *   Return:     float32 in pixles.
    *******************************************************************************************************************/
    float32 DebugDraw::toPixels(const float32 meters)
    {
        return meters * pixelsPerMeter;
    }


    /***************************************************************************************************************//**
    *   @brief  This method draws all box2d objects to the screen.
    *   @param  target the window or other render target where the objects will be drawn.
    *   @param  states struct that contains different rendering properties.
	*   pre:        This class must first be registered with a box2d world object.
	*   pre:        The update method must be called before draw.
    *   side:       modifies the target by drawing to it
    *******************************************************************************************************************/
    void DebugDraw::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        UNUSED(states);
        target.draw(triangles);
        target.draw(lines);
    }


    /*******************************************************************************************************************
    *   @brief  This method draws a single point.
    *   @param  p The center point of the point to be drawn.
    *   @param  size the radius of the point to be drawn.
    *   @param  color the color of the point to be drawn.
    *******************************************************************************************************************/
    void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
    {
        DrawCircle(p, size, color);
    }


    /*******************************************************************************************************************
    *   Destructor
    *******************************************************************************************************************/
    DebugDraw::~DebugDraw()
    {
        //dtor
    }

namespace
{
    /**********************************************************************************************
    *   Purpose:    This method converts a circle to points along the circumference of the circle.
    *   Input:      const b2Vec2& the center of the circle.
    *               float32 the radius of the circle.
    *               const unsigned the number of points around the circumference to be created.
    *   return:     std::vector<b2Vec2> a vector of points along the circumference.
    **********************************************************************************************/
    std::vector<b2Vec2> getPoints(const b2Vec2& center, float32 radius, const unsigned pointCount)
    {

        std::vector<b2Vec2> tempVec;
        for(unsigned i = 1; i <= pointCount; ++i)
        {
            b2Vec2 point;
            float angle = i * TAU / pointCount;
            point.x = center.x + (cos(angle) * radius);
            point.y = center.y + (sin(angle) * radius);
            tempVec.push_back(point);
        }

        return tempVec;
    }


    /****************************************************************************************
    *   Purpose:    This converts a box2d color object to an SFML color object.
    *   Input:      const b2Color &color this parameter is a box2d color which will be
    *               converted to an SFML color.
    *               int alpha this parameter represents the alpha (opacity) of the color.
    *   Return:     sf::Color object which is created from the input parameters.
    ****************************************************************************************/
    sf::Color toSfColor(const b2Color &color, int alpha)
    {
        UNUSED(alpha); 
        return sf::Color (sf::Uint8(color.r * 255), sf::Uint8(color.g * 255), sf::Uint8(color.b * 255));
    }

}
