#ifndef STATEBASE_H
#define STATEBASE_H
#include <GameUtilities/Engin/GameState.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Box2D/Box2D.h>
#include <memory>
#include "DebugDraw.h"

class StateBase: public Engin::GameState
{
    public:
        StateBase();
        virtual ~StateBase();
    protected:
        static sf::RenderWindow window;
        static std::unique_ptr<b2World> world;
        	float32 timeStep = 1 / 20.0;      //the length of time passed to simulate (seconds)
            int32 velocityIterations = 8;   //how strongly to correct velocity
            int32 positionIterations = 3;   //how strongly to correct position
            //DebugDraw debugDraw;
};

#endif // STATEBASE_H
