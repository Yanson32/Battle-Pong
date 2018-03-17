#ifndef INTROSTATE_H
#define INTROSTATE_H

/************************************************************//**
*   @author Wayne J Larson Jr
*   @date   12/24/17
*   @brief  IntroState is the first state seen by the user.
****************************************************************/

#include <GameUtilities/Engin/Engin.h>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
//#include <SFML/Graphics/Font.hpp>

#include "States/StateBase.h"

class IntroState: public StateBase
{
    public:
        /****************************************************************//**
        *   @brief  Constructor
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        IntroState(GU::Engin::Engin& engin);


        /****************************************************************//**
        *   @brief  This method handles input such as user input and events.
        *           This should be called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void HandleEvents(GU::Engin::Engin& engin, const int &deltaTime) override;


        /****************************************************************//**
        *   @brief  This method updates the game logic. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void Update(GU::Engin::Engin& engin, const int &deltaTime) override;


        /****************************************************************//**
        *   @brief  This method draws the current frame. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void Draw(GU::Engin::Engin& engin, const int &deltaTime) override;

        virtual void Init() override;
        virtual void Clean() override;
        void sfEvent(GU::Engin::Engin& engin, const sf::Event &event);
        void guEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event);

        /****************************************************************//**
        *   @brief  Destructor
        ********************************************************************/
        virtual ~IntroState();
    private:

        /****************************************************************//**
        *   @brief  This method is a callback for the start button
        ********************************************************************/
        void onStartPressed();

        /****************************************************************//**
        *   @brief  This method is a callback for the options button
        ********************************************************************/
        void onOptionsPressed();

        void onMultiplayerPressed();
        sf::Text header;                            ///Text displayed at the top of the screen
        sf::Color background = sf::Color::Black;    ///Color used to clear the screen background
        //sf::Font headerFont;                      ///Font used for the screens header
        tgui::Button::Ptr startButton;
        tgui::Button::Ptr optionButton;
        tgui::Button::Ptr multiplayerButton;
};

#endif // INTROSTATE_H
