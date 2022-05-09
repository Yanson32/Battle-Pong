#ifndef PONG_CREDITS_STATE_H
#define PONG_CREDITS_STATE_H 

/************************************************************//**
*   @author Wayne J Larson Jr
*   @date   05/08/22
*   @brief  
****************************************************************/

#include "States/StateBase.h"
#include "Objects/Ball.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Clock.hpp>

#include <memory>

#include "Box2D/DebugDraw.h"
#include <TGUI/TGUI.hpp>

#include <GameUtilities/Engin/Frame.h>

class CreditsState: public StateBase
{
    public:
        /****************************************************************//**
        *   @brief  Constructor
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        CreditsState(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow, DebugDraw &debugDraw, tgui::Gui &newGui, const StateId newId = StateId::CREDITS_STATE);

        void sfEvent(GU::Engin::Engin& engin, const sf::Event &event, std::shared_ptr<GU::Engin::Frame> frame);
        void handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event, std::shared_ptr<GU::Engin::Frame> frame);
        virtual void Init(std::shared_ptr<GU::Engin::Frame> frame) override;
        virtual void Clean(std::shared_ptr<GU::Engin::Frame> frame) override;

        /****************************************************************//**
        *   @brief  This method handles input such as user input and events.
        *           This should be called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        void HandleEvents(GU::Engin::Engin& newEngin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame) override;


        /****************************************************************//**
        *   @brief  This method updates the game logic. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        void Update(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame) override;


        /****************************************************************//**
        *   @brief  This method draws the current frame. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        void Draw(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame) override;


        /****************************************************************//**
        *   @brief  Destructor
        ********************************************************************/
        ~CreditsState();
    private:
};
#endif
