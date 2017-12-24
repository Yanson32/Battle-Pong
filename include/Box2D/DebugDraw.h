#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H
#include "Box2D/Common/b2Draw.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Drawable.hpp>
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

/************************************************************************************************************
*   Author:     Wayne J Larson Jr.
*   Date:       2/6/17
*   Purpose:    This class is used for drawing box2d objects with SFML.
************************************************************************************************************/
class DebugDraw: public b2Draw, public sf::Drawable
{
    public:
        /****************************************************************************************************
        *   Purpose:    This method is a constructor.
        *   Input:      sf::RenderWindow &newWindow this is the window where the Box2D bodies will be drawn
        ****************************************************************************************************/
        DebugDraw(b2World& newWorld, const float newPixelsPerMeter = 40.0f);

		/*******************************************************************************************************************
		*   Purpose:    This method draws axis alligned bounding boxes.
		*   Input:      b2Vec2* vertices which is an array of verticies.
		*               int32 vertexCount the number of vertices in the vertices parameter.
		*               const b2Color which is the color the axis aligned bounding box should be drawn with
		*   pre:        This class must first be registered with a box2d world object.
		*               The e_aabbBit must be set.
		*******************************************************************************************************************/
		void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

        /****************************************************************************************************
        *   Purpose:    This method draws all box2d objects to the screen.
        *   Input:      sf::RenderTarget the window or other render target where the objects will be drawn.
        *               sf::RenderStates struct that contains different rendering properties.
        *   side:       modifies the target by drawing to it
        ****************************************************************************************************/
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /*******************************************************************************************************************
        *   Purpose:    This method draws axis alligned bounding boxes.
        *   Input:      b2Vec2* vertices which is an array of verticies.
        *               int32 vertexCount the number of vertices in the vertices parameter.
        *               const b2Color which is the color the axis aligned bounding box should be drawn with
        *   pre:        This class must first be registered with a box2d world object.
        *               The e_aabbBit must be set.
        *******************************************************************************************************************/
        virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;


        /*******************************************************************************************************************
        *   Purpose:    This method draws the outline of a circle.
        *   Input:      const b2Vec2& center this parameter is the center of the circle.
        *               float32 radius this parameter is the radius of the circle.
        *               const b2Color& color this parameter is the color that the circle will be drawn with
        *   Pre:        This class must first be registered with a box2d world object.
        *******************************************************************************************************************/
        virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;


        /*******************************************************************************************************************
        *   Purpose:    This method draws circle objects. The circle will be drawn as a circle filled with color.
        *               float32 radius this is the radius of the circle.
        *               const b2Vec2 axis is a direction vector relative to the center of the circle. The axis parameter must
        *               be scaled by the radius of the circle to compensate for the diameter of the circle.
        *               const b2Color color this is the color the circle will be drawn in.
        *   Pre:        This class must first be registered with a box2d world object.
        *               The e_shapeBit must be set.
        ********************************************************************************************************************/
        virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;


        /*******************************************************************************************************************
        *   Purpose:    This method draws a line segment to the screen.
        *   Input:      const b2Vec2 p1 this is the first point of the line segment.
        *               const b2Vec2 p2 this is the second point of the line segment.
        *               const b2Color color this is a struct that defines the blue, green, red color values.
        *   Pre:        This class must first be registered with a box2d world object.
        *               The e_shapeBit must be set.
        *******************************************************************************************************************/
        virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;


        /*******************************************************************************************************************
        *   Purpose:    This method draws a transform to the screen when the e_centerOfMassBit is set.
        *   Input:      const b2Transform xf which is the transform to be drawn to the screen.
        *   Pre:        This class must first be registered with a box2d world object.
        *               The e_centerOfMassBit must be set or the function won't be called
        *******************************************************************************************************************/
        virtual void DrawTransform(const b2Transform& xf) override;

		virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override;

        /*******************************************************************************************************************
        *   Purpose:    This method does per frame logic and must be called once per frame.
        *******************************************************************************************************************/
        void update();


        /*******************************************************************************************************************
        *   Destructor
        *******************************************************************************************************************/
        virtual ~DebugDraw();

    private:
        /*******************************************************************************************************************
        *   Purpose:    This method converts b2Vec2 in box2d meters to sf::Vector2f in pixles.
        *   Input:      const b2Vec2 the point in box2d meters.
        *   Return:     sf::Vector2f the point in pixles.
        *******************************************************************************************************************/
        sf::Vector2f toPixels(const b2Vec2 &vec);


        /*******************************************************************************************************************
        *   Purpose:    This method converts float32 in box2d meters to float32 in pixles.
        *   Input:      const float32 in meters
        *   Return:     float32 in pixles.
        *******************************************************************************************************************/
        float32 toPixels(const float32 meters);


        sf::VertexArray lines;
        sf::VertexArray triangles;
        unsigned linesUsed = 0;
        unsigned trianglesUsed = 0;
        sf::FloatRect viewBounds;
        const float pixelsPerMeter;
        b2World &world;
};

#endif // DEBUGDRAW_H
