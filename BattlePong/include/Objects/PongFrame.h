#ifndef PONGFRAME_H
#define PONGFRAME_H
#include <memory>
#include "Objects/Objects.h"
#include "Box2D/DebugDraw.h"
#include <TGUI/TGUI.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Input/AI.h"
#include <GameUtilities/Engin/Engin.h>
#include <GameUtilities/Engin/Frame.h>
#include "Box2D/ContactListener.h"

class PongFrame: public GU::Engin::Frame
{
    public:
        PongFrame(const sf::Vector2f &windowSize);
        std::shared_ptr<b2World> world;          ///The Box2D physics engin world object
        std::shared_ptr<DebugDraw> debugDraw;    ///The Box2D b2Draw subclass for debug drawing
        std::unique_ptr<Ball> ball;              ///Pointer to the ball object
        std::unique_ptr<Wall> ground;            ///Pointer to the bottem box2D object representing the ground
        std::unique_ptr<Wall> celing;            ///Pointer to the celing Box2D object
        std::unique_ptr<Wall> leftWall;          ///Pointer to the left wall Box2D object
        std::unique_ptr<Wall> rightWall;         ///Pointer to the right wall Box2D object
        std::unique_ptr<Paddle> leftPaddle;      ///Pointer to the paddle on the left side of the screen
        std::unique_ptr<Paddle> rightPaddle;     ///Pointer to the paddle on the right side of the screen
        std::unique_ptr<Goal> leftGoal;          ///Pointer to the goal sensor which determines is a goal has been scored on the left player
        std::unique_ptr<Goal> rightGoal;         ///Pointer to the goal sensor which determines is a goal has been scored on the right player
        std::unique_ptr<PaddleStop> bottomPaddleStop;
        std::unique_ptr<PaddleStop> topPaddleStop;
        virtual void Init();
        virtual void Clean();
        virtual void HandleEvents(GU::Engin::Engin& engin, const float &deltaTime);
        virtual void Update(GU::Engin::Engin& engin, const float &deltaTime);
        virtual void Draw(GU::Engin::Engin& engin, const float &deltaTime);
        virtual ~PongFrame();
    private:
        ContactListener contactListener;
};

#endif  
