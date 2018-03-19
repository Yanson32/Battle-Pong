#ifndef MUSICSTATE_H
#define MUSICSTATE_H

#include "States/StateBase.h"
#include <GameUtilities/Engin/Engin.h>

class MusicState: public StateBase
{
    public:
        MusicState(GU::Engin::Engin& engin);
        void sfEvent(GU::Engin::Engin& engin, const sf::Event &event);
        void handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event);
        virtual void Init();
        virtual void Clean();

        /****************************************************************//**
        *   @brief  This method handles input such as user input and events.
        *           This should be called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        virtual void HandleEvents(GU::Engin::Engin& newEngin, const int &deltaTime) override;


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

        virtual ~MusicState();
    protected:
    private:
        void onBackPressed();
        //tgui::EditBox::Ptr eBox;
        //tgui::ComboBox::Ptr cBox;
        tgui::Button::Ptr backButton;
};

#endif // MUSICSTATE_H
