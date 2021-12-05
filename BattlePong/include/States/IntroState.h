#ifndef INTROSTATE_H
#define INTROSTATE_H

/************************************************************//**
*   @author Wayne J Larson Jr
*   @date   12/24/17
*   @brief  IntroState is the first state seen by the user.
****************************************************************/

#include <GameUtilities/Engin/Engin.h>
#include <GameUtilities/Engin/Frame.h>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
//#include <SFML/Graphics/Font.hpp>

#include "States/StateBase.h"
#include "Gui/GuiManager.h"

#include "Box2D/DebugDraw.h"
#include <TGUI/TGUI.hpp>

class IntroState: public StateBase
{
    public:
        /****************************************************************//**
        *   @brief  Constructor
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        IntroState(GU::Engin::Engin& engin, sf::RenderWindow &newWindow, DebugDraw &debugDraw, tgui::Gui &newGui);


        /****************************************************************//**
        *   @brief  This method handles input such as user input and events.
        *           This should be called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void HandleEvents(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame) override;


        /****************************************************************//**
        *   @brief  This method updates the game logic. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void Update(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame) override;


        /****************************************************************//**
        *   @brief  This method draws the current frame. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void Draw(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame) override;

        void handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event, std::shared_ptr<GU::Engin::Frame> frame);
        void sfEvent(GU::Engin::Engin& engin, const sf::Event &event, std::shared_ptr<GU::Engin::Frame> frame);
        virtual void Init(std::shared_ptr<GU::Engin::Frame> frame) override;
        virtual void Clean(std::shared_ptr<GU::Engin::Frame> frame) override;

        /****************************************************************//**
        *   @brief  Destructor
        ********************************************************************/
        virtual ~IntroState();
    private:
        sf::Text header;                            ///Text displayed at the top of the screen
        sf::Color background = sf::Color::Black;    ///Color used to clear the screen background
        //sf::Font headerFont;                      ///Font used for the screens header
};

#endif // INTROSTATE_H
