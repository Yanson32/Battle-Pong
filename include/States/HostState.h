#ifndef HOSTSTATE_H
#define HOSTSTATE_H
#include "States/StateBase.h"

#include <TGUI/TGUI.hpp>
#include <memory>
//class HostPanel: public tgui::Panel
//{
//    public:
//        HostPanel();
//        void Init();
//        void Clean();
//    private:
////        tgui::Label::Ptr portLabel;
////        tgui::EditBox::Ptr portBox;
////        tgui::Button::Ptr hostButton;
//        void onBackPressed();
//
//};

class HostState: public StateBase
{
    public:
        HostState(Engin::Engin& engin);

        void sfEvent(Engin::Engin& engin, const sf::Event &event);
        void guEvent(Engin::Engin& engin, Evt::EventPtr event);

        /****************************************************************//**
        *   @brief  This method handles input such as user input and events.
        *           This should be called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void HandleEvents(Engin::Engin& engin, const int &deltaTime);


        /****************************************************************//**
        *   @brief  This method updates the game logic. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void Update(Engin::Engin& engin, const int &deltaTime);


        /****************************************************************//**
        *   @brief  This method draws the current frame. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void Draw(Engin::Engin& engin, const int &deltaTime);

        virtual void Init() override;
        virtual void Clean() override;
        virtual ~HostState();
    protected:
    private:
        //static std::shared_ptr<HostPanel> panel;
        tgui::Button::Ptr backButton;
        tgui::Label::Ptr localIpLabel;
        tgui::EditBox::Ptr localIpBox;
        tgui::Label::Ptr globalIpLabel;
        tgui::EditBox::Ptr globalIpBox;
        tgui::Label::Ptr portLabel;
        tgui::EditBox::Ptr portBox;
        tgui::Button::Ptr hostButton;
        void onBackPressed();
        void onHostPressed();
};

#endif // HOSTSTATE_H
