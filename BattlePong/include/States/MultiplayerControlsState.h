#ifndef MultiplayerControlState_H
#define MultiplayerControlState_H
#include <TGUI/TGUI.hpp>
#include "States/StateBase.h"



class MultiplayerControlState: public StateBase
{
    public:
        MultiplayerControlState(GU::Engin::Engin& engin);
        void sfEvent(GU::Engin::Engin& engin, const sf::Event &event);
        void guEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event);
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
