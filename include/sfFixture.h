#ifndef SFFIXTURE_H
#define SFFIXTURE_H
#include <Box2D/Box2D.h>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>

class sfFixture: public b2Fixture, public sf::Shape
{
    public:
        sfFixture();
        std::size_t getPointCount() const;
        sf::Vector2f getPoint(std::size_t index) const;
        virtual ~sfFixture();
    protected:
    private:
};

#endif // SFFIXTURE_H
