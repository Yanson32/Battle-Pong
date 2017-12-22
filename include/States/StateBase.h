#ifndef STATEBASE_H
#define STATEBASE_H
#include <GameUtilities/Engin/GameState.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Box2D/Box2D.h>
#include <memory>
#include "DebugDraw.h"
#include <TGUI/TGUI.hpp>

class Wall;
class Paddle;
class Ball;

class StateBase: public Engin::GameState
{
    public:
        StateBase();
        virtual ~StateBase();
    protected:
        static sf::RenderWindow window;
        static tgui::Gui gui;
        static std::unique_ptr<b2World> world;
        static DebugDraw debugDraw;
        Ball* ball = nullptr;
        Wall* ground = nullptr;
        Wall* celing = nullptr;
        Wall* leftWall = nullptr;
        Wall* RightWall = nullptr;
        Paddle* leftPaddle = nullptr;
        Paddle* rightPaddle = nullptr;
        float32 timeStep = 1 / 20.0;      //the length of time passed to simulate (seconds)
        int32 velocityIterations = 8;   //how strongly to correct velocity
        int32 positionIterations = 3;   //how strongly to correct position


};

#endif // STATEBASE_H
