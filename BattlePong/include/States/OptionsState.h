#ifndef OPTIONSSTATE_H
#define OPTIONSSTATE_H

/************************************************************//**
*   @author Wayne J Larson Jr
*   @date   12/24/17
*   @brief  OptionsState is a screen where the user can navigate
*           to the various game options.
****************************************************************/

#include "States/StateBase.h"

class OptionsState: public StateBase
{
    public:
        /****************************************************************//**
        *   @brief  Constructor
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        OptionsState(GU::Engin::Engin& engin);

        virtual void Init();
        virtual void Clean();
        /****************************************************************//**
        *   @brief  This method handles input such as user input and events.
        *           This should be called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void HandleEvents(GU::Engin::Engin& newEngin, const float &deltaTime) override;


        /****************************************************************//**
        *   @brief  This method updates the game logic. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void Update(GU::Engin::Engin& engin, const float &deltaTime) override;


        /****************************************************************//**
        *   @brief  This method draws the current frame. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void Draw(GU::Engin::Engin& engin, const float &deltaTime) override;


        /****************************************************************//**
        *   @brief  Destructor
        ********************************************************************/
        virtual ~OptionsState();
    protected:
    private:
    /****************************************************************//**
    *   @brief  This method is a callback for the music button
    ********************************************************************/
    void onMusicPressed();


    /****************************************************************//**
    *   @brief  This method is a callback for the control button
    ********************************************************************/
    void onControlsPressed();


    /****************************************************************//**
    *   @brief  This method is a callback for the back button
    ********************************************************************/
    void onBackPressed();

    void onLoadPressed();

    void onSavePressed();

    tgui::Button::Ptr controlsButton;
    tgui::Button::Ptr musicButton;
    tgui::Button::Ptr loadButton;
    tgui::Button::Ptr saveButton;
    tgui::Button::Ptr backButton;

};

#endif // OPTIONSSTATE_H
