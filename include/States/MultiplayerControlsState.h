#ifndef MULTIPLAYERSTATE_H
#define MULTIPLAYERSTATE_H
#include <TGUI/TGUI.hpp>
#include "States/StateBase.h"

class MultiplayerPanel: public tgui::Panel
{
    public:
        MultiplayerPanel();
        void Init();
    private:
        tgui::Label::Ptr ipLabel;
        tgui::EditBox::Ptr ipBox;
        tgui::Label::Ptr portLabel;
        tgui::EditBox::Ptr portBox;
        tgui::Button::Ptr hostButton;
        void onHostPressed();
};

class MultiplayerState: public StateBase
{
    public:
        MultiplayerState(Engin::Engin& engin);

        virtual void Init();
        virtual void Clean();
        /****************************************************************//**
        *   @brief  This method handles input such as user input and events.
        *           This should be called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void HandleEvents(Engin::Engin& newEngin, const int &deltaTime) override;


        /****************************************************************//**
        *   @brief  This method updates the game logic. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void Update(Engin::Engin& engin, const int &deltaTime) override;


        /****************************************************************//**
        *   @brief  This method draws the current frame. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void Draw(Engin::Engin& engin, const int &deltaTime) override;

        void onBackPressed();
        virtual ~MultiplayerState();
    protected:
    private:
        tgui::Button::Ptr backButton;
        static std::shared_ptr<MultiplayerPanel> panel;
};

#endif // MULTIPLAYERSTATE_H
