#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H
#include "Box2D/Common/b2Draw.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Drawable.hpp>
/***************************************************************************
*   @author Wayne J Larson Jr.
*   @date   2/6/17
*   @brief  This class is used for drawing box2d objects with SFML.
***************************************************************************/


namespace sf
{
    class RenderWindow;
    class RenderStates;
    class RenderTarget;
}

struct b2Vec2;
struct b2Color;
struct b2Transform;
struct b2World;


class DebugDraw: public b2Draw, public sf::Drawable
{
    public:
        /***************************************************************************************************************//**
        *   @brief  This method is a constructor.
        *   @param  newWorld a reference to a Box2D world object which will
        *           be stored internally untill object deletion.
        *   @param  newPixelsPerMeter is used to convert between pixles and
        *           Box2D meters
        *******************************************************************************************************************/
        DebugDraw(b2World& newWorld, const float newPixelsPerMeter = 40.0f);


		/***************************************************************************************************************//**
		*   @brief  This method draws axis alligned bounding boxes.
		*   @param  vertices which is an array of verticies.
		*   @param  vertexCount the number of vertices in the vertices parameter.
		*   @param  color which is the color the axis aligned bounding box should be drawn with
		*   pre:        This class must first be registered with a box2d world object.
		*               The e_aabbBit must be set.
		*******************************************************************************************************************/
		void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);


        /***************************************************************************************************************//**
        *   @brief  This method draws all box2d objects to the screen.
        *   @param  target the window or other render target where the objects will be drawn.
        *   @param  states struct that contains different rendering properties.
        *   side:       modifies the target by drawing to it
        *******************************************************************************************************************/
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /***************************************************************************************************************//**
        *   @brief  This method draws axis alligned bounding boxes.
        *   @param  vertices which is an array of verticies.
        *   @param  vertexCount the number of vertices in the vertices parameter.
        *   @param  color which is the color the axis aligned bounding box should be drawn with
        *   pre:        This class must first be registered with a box2d world object.
        *               The e_aabbBit must be set.
        *******************************************************************************************************************/
        virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;


        /***************************************************************************************************************//**
        *   @brief  This method draws the outline of a circle.
        *   @param  const b2Vec2& center this parameter is the center of the circle.
        *   @param  radius this parameter is the radius of the circle.
            @param  color this parameter is the color that the circle will be drawn with
        *   Pre:        This class must first be registered with a box2d world object.
        *******************************************************************************************************************/
        virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;


        /***************************************************************************************************************//**
        *   @brief  This method draws circle objects. The circle will be drawn as a circle filled with color.
        *   @param  center the center point in meters of the circle to be drawn
        *   @param  radius this is the radius of the circle.
        *   @param  axis is a direction vector relative to the center of the circle. The axis parameter must
        *           be scaled by the radius of the circle to compensate for the diameter of the circle.
        *   @param  color this is the color the circle will be drawn in.
        *   Pre:        This class must first be registered with a box2d world object.
        *               The e_shapeBit must be set.
        ********************************************************************************************************************/
        virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;


        /*******************************************************************************************************************
        *   @brief  This method draws a line segment to the screen.
        *   @param  p1 this is the first point of the line segment.
        *   @param  p2 this is the second point of the line segment.
        *   @param  color this is a struct that defines the blue, green, red color values.
        *   Pre:        This class must first be registered with a box2d world object.
        *               The e_shapeBit must be set.
        *******************************************************************************************************************/
        virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;


        /*******************************************************************************************************************
        *   @brief  This method draws a transform to the screen when the e_centerOfMassBit is set.
        *   @param  xf which is the transform to be drawn to the screen.
        *   Pre:        This class must first be registered with a box2d world object.
        *               The e_centerOfMassBit must be set or the function won't be called
        *******************************************************************************************************************/
        virtual void DrawTransform(const b2Transform& xf) override;


        /*******************************************************************************************************************
        *   @brief  This method draws a single point.
        *   @param  p The center point of the point to be drawn.
        *   @param  size the radius of the point to be drawn.
        *   @param  color the color of the point to be drawn.
        *******************************************************************************************************************/
		virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override;


        /*******************************************************************************************************************
        *   @param  This method does per frame logic and must be called once per frame.
        *******************************************************************************************************************/
        void update();


        /*******************************************************************************************************************
        *   @brief  Destructor
        *******************************************************************************************************************/
        virtual ~DebugDraw();

    private:
        /*******************************************************************************************************************
        *   @brief  This method converts b2Vec2 in box2d meters to sf::Vector2f in pixles.
        *   @param  vec the point in box2d meters.
        *   @return the point in pixles.
        *******************************************************************************************************************/
        sf::Vector2f toPixels(const b2Vec2 &vec);


        /*******************************************************************************************************************
        *   @brief  This method converts float32 in Box2D meters to float32 in pixles.
        *   @param  meters a floating point value on Box2D meters
        *   @return float32 in pixles.
        *******************************************************************************************************************/
        float32 toPixels(const float32 meters);


        sf::VertexArray lines;          ///This contains SFML line primitives for drawing lines.
        sf::VertexArray triangles;      ///This contains SFML triangle primitives for drawing convex shapes except lines.
        unsigned linesUsed = 0;         ///This used to resize the lines vector on each iteration so the vector dosen't grow to large.
        unsigned trianglesUsed = 0;     ///This used to resize the triangles vector on each iteration so the vector dosen't grow to large.
        const float pixelsPerMeter;     ///This is used to convert between pixles and meters.
        b2World &world;                 ///Box2D world object.
};

#endif // DEBUGDRAW_H
