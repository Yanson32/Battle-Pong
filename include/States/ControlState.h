#ifndef CONTROLSTATE_H
#define CONTROLSTATE_H
/************************************************************//**
*   @author Wayne J Larson Jr
*   @date   12/24/17
*   @brief  ControlState Displays a screen with two buttons.
*           One for each paddle. Selecting one will bring you
*           into that paddles options screen.
****************************************************************/

#include "States/StateBase.h"

class ControlState: public StateBase
{
    public:
        /****************************************************************//**
        *   @brief  Constructor
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        ControlState(Engin::Engin& newEngin);


        /****************************************************************//**
        *   @brief  This method handles input such as user input and events.
        *           This should be called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void HandleEvents(Engin::Engin& newEngin) override;


        /****************************************************************//**
        *   @brief  This method updates the game logic. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void Update(Engin::Engin& engin) override;


        /****************************************************************//**
        *   @brief  This method draws the current frame. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void Draw(Engin::Engin& engin) override;


        /****************************************************************//**
        *   @brief  Destructor
        ********************************************************************/
        virtual ~ControlState();
    private:
        /****************************************************************//**
        *   @brief  This method is a callback for the Paddle 1 button
        ********************************************************************/
        void onPaddle1();


        /****************************************************************//**
        *   @brief  This method is a callback for the Paddle 2 button
        ********************************************************************/
        void onPaddle2();


        /****************************************************************//**
        *   @brief  This method is a callback for the back button
        ********************************************************************/
        void onBack();
};

#endif // CONTROLSTATE_H

