#ifndef PONG_PLAYSTATE_H
#define PONG_PLAYSTATE_H

/************************************************************//**
*   @author Wayne J Larson Jr
*   @date   12/24/17
*   @brief  PlayState This state is where the game logic is
*           executed.
****************************************************************/

#include "States/StateBase.h"
#include "Objects/Ball.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Clock.hpp>

#include <memory>

class PlayState: public StateBase
{
    public:
        /****************************************************************//**
        *   @brief  Constructor
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        PlayState(Engin::Engin& newEngin, const stateId newId = stateId::PLAY_STATE);

        void sfEvent(Engin::Engin& engin, const sf::Event &event);
        void guEvent(Engin::Engin& engin, Evt::EventPtr event);
        virtual void Init() override;
        virtual void Clean() override;

        /****************************************************************//**
        *   @brief  This method handles input such as user input and events.
        *           This should be called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        void HandleEvents(Engin::Engin& newEngin, const int &deltaTime);


        /****************************************************************//**
        *   @brief  This method updates the game logic. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        void Update(Engin::Engin& engin, const int &deltaTime);


        /****************************************************************//**
        *   @brief  This method draws the current frame. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        void Draw(Engin::Engin& engin, const int &deltaTime);


        /****************************************************************//**
        *   @brief  Destructor
        ********************************************************************/
        ~PlayState();
    private:

};
#endif
