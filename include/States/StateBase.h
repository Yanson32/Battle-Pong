#ifndef STATEBASE_H
#define STATEBASE_H

/************************************************************//**
*   @author Wayne J Larson Jr
*   @date   12/24/17
*   @brief  StateBase This is the parent class for all states.
****************************************************************/

#include <GameUtilities/Engin/GameState.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Box2D/Box2D.h>
#include <memory>
#include <TGUI/TGUI.hpp>

#include "Box2D/DebugDraw.h"
#include "Box2D/ContactListener.h"

#include "Objects/Goal.h"

#include "Events/Listeners/MusicListener.h"
#include "Events/Listeners/SoundListener.h"
#include "Events/Listeners/BallCollisionListener.h"
#include "Events/Listeners/GoalCollisionListener.h"
#include "Events/Listeners/LeftPaddleGoalListener.h"
#include "Events/Listeners/RightPaddleGoalListener.h"

#include "PaddleHud.h"

class Wall;
class Paddle;
class Ball;

namespace Engin
{
    class Engin;
}

class StateBase: public Engin::GameState
{
    public:
        /****************************************************************//**
        *   @brief  Constructor
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        StateBase(Engin::Engin& newEngin);


        virtual void Init() override = 0;
        virtual void Clean() override = 0;

        /****************************************************************//**
        *   @brief  This method handles input such as user input and events.
        *           This should be called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void HandleEvents(Engin::Engin& engin, const int &deltaTime) = 0;


        /****************************************************************//**
        *   @brief  This method updates the game logic. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void Update(Engin::Engin& engin, const int &deltaTime) = 0;


        /****************************************************************//**
        *   @brief  This method draws the current frame. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void Draw(Engin::Engin& engin, const int &deltaTime) override;


        /****************************************************************//**
        *   @brief  This method allows the system to pause the game.
        *           When system pause is in effect regular pause won't
        *           work.
        *   @param  newSysPaus true if the system is pausing the game and,
        *           false otherwise.
        ********************************************************************/
        void systemPause(const bool newSysPause);


        /****************************************************************//**
        *   @brief  Checks to see if system pause is in effect.
        *   @return boolean true if system pause is in effect and false
        *           otherwise.
        ********************************************************************/
        bool isSystemPaused() const;

        void gameEvents();
        void reset();
        /****************************************************************//**
        *   @brief  Destructor
        ********************************************************************/
        virtual ~StateBase();
    protected:
        static sf::RenderWindow window;                 ///The game's window
        static tgui::Gui gui;                           ///The Main TGUI object
        static std::shared_ptr<b2World> world;          ///The Box2D physics engin world object
        static DebugDraw debugDraw;                     ///The Box2D b2Draw subclass for debug drawing
        static std::unique_ptr<Ball> ball;              ///Pointer to the ball object
        static std::unique_ptr<Wall> ground;            ///Pointer to the bottem box2D object representing the ground
        static std::unique_ptr<Wall> celing;            ///Pointer to the celing Box2D object
        static std::unique_ptr<Wall> leftWall;          ///Pointer to the left wall Box2D object
        static std::unique_ptr<Wall> RightWall;         ///Pointer to the right wall Box2D object
        static std::unique_ptr<Paddle> leftPaddle;      ///Pointer to the paddle on the left side of the screen
        static std::unique_ptr<Paddle> rightPaddle;     ///Pointer to the paddle on the right side of the screen
        static std::unique_ptr<Goal> leftGoal;
        static std::unique_ptr<Goal> rightGoal;
        static sf::Sound sound;
        static sf::Music music;
        static std::shared_ptr<PaddleHud> paddle1Hud;
        static std::shared_ptr<PaddleHud> paddle2Hud;
        static ContactListener contactListener;         ///Subclass of Box2D b2ContactListener used to detect Box2D collisions
        static sf::Text userMessage;                    ///Text displayed in the center of the screen
        static sf::Clock messageClock;                  ///This clock object is used to time the beginning message "Ready!, 3, 2, 1, Go!
        float32 timeStep = 1 / 20.0;                    ///Box2D the length of time passed to simulate (seconds)
        int32 velocityIterations = 8;                   ///Box2D how strongly to correct velocity
        int32 positionIterations = 3;                   ///Box2D how strongly to correct position
        Engin::Engin &engin;                            ///The Main game engin
        bool sysPause;                                  ///True when the system is paused and false otherwise

};

#endif // STATEBASE_H
