#ifndef STATEBASE_H
#define STATEBASE_H

/************************************************************//**
*   @author Wayne J Larson Jr
*   @date   12/24/17
*   @brief  StateBase This is the parent class for all states.
****************************************************************/

#include <GameUtilities/Engin/GameState.h>
#include <GameUtilities/Event/EventHandler.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>

#include <Box2D/Box2D.h>
#include <memory>
#include <TGUI/TGUI.hpp>

#include "Box2D/DebugDraw.h"
#include "Box2D/ContactListener.h"

#include "Objects/Goal.h"
#include "Objects/PaddleStop.h"

#include "Gui/PaddleHud.h"
#include "Logging.h"
#include "States/Id.h"

#include <memory>
#include <TGUI/TGUI.hpp>

#include "Objects/Frame.h"

class Wall;
class Paddle;
class Ball;
namespace GU
{
    namespace Engin
    {
        class Engin;
    }
}
class StateBase: public GU::Engin::GameState, public GU::Evt::EventHandler
{
    public:
        /****************************************************************//**
        *   @brief  Constructor
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        StateBase(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow, std::shared_ptr<Frame> newFrame, DebugDraw &newDebugDraw, tgui::Gui &newGui, const stateId newState);


        virtual void Init() override;
        virtual void Clean() override = 0;

        /****************************************************************//**
        *   @brief  This method handles input such as user input and events.
        *           This should be called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void HandleEvents(GU::Engin::Engin& engin, const float &deltaTime) = 0;


        /****************************************************************//**
        *   @brief  This method updates the game logic. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void Update(GU::Engin::Engin& engin, const float &deltaTime);


        /****************************************************************//**
        *   @brief  This method draws the current frame. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void Draw(GU::Engin::Engin& engin, const float &deltaTime) override;



        void sfEvent(GU::Engin::Engin& engin, const sf::Event &event);
        void handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event);
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
        void centerText();
        bool isBallOnScreen();
        GU::Engin::Engin &engin;                        ///The Main game engin
        sf::RenderWindow &window;
        std::shared_ptr<Frame> frame;
        DebugDraw &debugDraw;
        tgui::Gui &gui;                           ///The Main TGUI object
        stateId state;
        static sf::Sound sound;
        static sf::Music music;
        static std::shared_ptr<PaddleHud> paddle1Hud;
        static std::shared_ptr<PaddleHud> paddle2Hud;
        static ContactListener contactListener;         ///Subclass of Box2D b2ContactListener used to detect Box2D collisions
        static sf::Text userMessage;                    ///Text displayed in the center of the screen
        static sf::Clock messageClock;                  ///This clock object is used to time the beginning message "Ready!, 3, 2, 1, Go!
        static sf::Clock roundClock;                    ///This clock tracks the time for each round and resets the game when the time has expired
        float32 timeStep = 1 / 20.0;                    ///Box2D the length of time passed to simulate (seconds)
        int32 velocityIterations = 8;                   ///Box2D how strongly to correct velocity
        int32 positionIterations = 8;                   ///Box2D how strongly to correct position
        bool sysPause;                                  ///True when the system is paused and false otherwise
        static sf::Texture backgroundTexture;
        static sf::RectangleShape backgroundRect;
        //boost::log::sources::severity_logger< logging::trivial::severity_level > log;

};

#endif // STATEBASE_H
