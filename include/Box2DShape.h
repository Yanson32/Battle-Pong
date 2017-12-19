#ifndef BOX2DSHAPE_H
#define BOX2DSHAPE_H
#include <SFML/Graphics/Shape.hpp>
#include <Box2D/Box2D.h>

class Box2DShape: public sf::Shape
{
    public:
        Box2DShape();
        std::size_t getPointCount() const;
        Vector2f getPoint(std::size_t index) const;
        virtual ~Box2DShape();
    protected:
    private:
        b2Body *body = nullptr;
};

#endif // BOX2DSHAPE_H
