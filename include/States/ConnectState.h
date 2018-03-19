#ifndef CONTROLSTATE_H
#define CONTROLSTATE_H
#include "States/StateBase.h"
#include <TGUI/TGUI.hpp>

class ConnectState: public StateBase
{
    public:
        ConnectState(GU::Engin::Engin& engin);
        /****************************************************************//**
        *   @brief  This method handles input such as user input and events.
        *           This should be called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void HandleEvents(GU::Engin::Engin& engin, const int &deltaTime);


        /****************************************************************//**
        *   @brief  This method updates the game logic. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void Update(GU::Engin::Engin& engin, const int &deltaTime);


        /****************************************************************//**
        *   @brief  This method draws the current frame. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void Draw(GU::Engin::Engin& engin, const int &deltaTime);

        virtual void Init() override;
        virtual void Clean() override;
        void sfEvent(GU::Engin::Engin& engin, const sf::Event &event);
        void handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event);
        virtual ~ConnectState();
    protected:
    private:
        //static std::shared_ptr<ConnectPanel> panel;
        tgui::Button::Ptr backButton;
        tgui::Label::Ptr ipLabel;
        tgui::EditBox::Ptr ipBox;
        tgui::Label::Ptr portLabel;
        tgui::EditBox::Ptr portBox;
        tgui::Button::Ptr connectButton;
        void onConnectPressed();
        void onBackPressed();
};

#endif // CONTROLSTATE_H
