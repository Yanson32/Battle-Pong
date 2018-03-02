#ifndef MultiplayerControlState_H
#define MultiplayerControlState_H
#include <TGUI/TGUI.hpp>
#include "States/StateBase.h"



class MultiplayerControlState: public StateBase
{
    public:
        MultiplayerControlState(Engin::Engin& engin);
        void sfEvent(Engin::Engin& engin, const sf::Event &event);
        void guEvent(Engin::Engin& engin, Evt::EventPtr event);
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
        virtual ~MultiplayerControlState();
    protected:
    private:
        tgui::Button::Ptr backButton;
        tgui::Button::Ptr hostButton;
        tgui::Button::Ptr connectButton;
        void onHostPressed();
        void onConnectPressed();
};

#endif // MultiplayerControlState_H
