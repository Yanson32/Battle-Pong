#ifndef PADDLESTATE_H
#define PADDLESTATE_H
/************************************************************//**
*   @author Wayne J Larson Jr
*   @date   12/24/17
*   @brief  PaddleState is a screen where options are presented
*           for a single paddle.
****************************************************************/

#include "States/StateBase.h"
#include "Settings.h"

class PaddleState: public StateBase
{
    public:
        /****************************************************************//**
        *   @brief  Constructor
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        *   @param  pSettings a pointer to a tgui panel containing
        *           paddle settings.
        ********************************************************************/
        PaddleState(Engin::Engin& newEngin, std::shared_ptr<PaddleSettings> pSettings);


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
        virtual ~PaddleState();
    private:
        /****************************************************************//**
        *   @brief  This method is a callback for the music button
        ********************************************************************/
        void onBack();


        /****************************************************************//**
        *   @brief
        ********************************************************************/
        void onNameBox();


        /****************************************************************//**
        *   @brief
        ********************************************************************/
        void onListItemSelected();

        tgui::EditBox::Ptr eBox;
        tgui::ComboBox::Ptr cBox;
        std::shared_ptr<PaddleSettings> paddleSettings;

};

#endif // PADDLESTATE_H
