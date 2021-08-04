#ifndef GOAL_H
#define GOAL_H
#include "Objects/ObjectBase.h"
#include "Events/Id.h"
#include <SFML/System/Vector2.hpp>
#include <array>
#include "Objects/ObjectId.h"

class Goal: public ObjectBase<sf::ConvexShape>
{
    public:
        Goal(std::shared_ptr<b2World> world, ObjectId newId, const std::array<sf::Vector2f, 4> vert);
        void update() override;
        virtual ~Goal();
    protected:
    private:
};

#endif // GOAL_H
