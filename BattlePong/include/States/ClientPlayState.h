#ifndef CLIENTPLAYSTATE_H
#define CLIENTPLAYSTATE_H

#include "States/PlayState.h"
#include <iostream>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

class ClientPlayState: public PlayState
{
    public:
        ClientPlayState(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow);

        virtual void Init() override;
        virtual void Clean() override;

        /****************************************************************//**
        *   @brief  This method handles input such as user input and events.
        *           This should be called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        void HandleEvents(GU::Engin::Engin& newEngin, const float &deltaTime) override;


        /****************************************************************//**
        *   @brief  This method updates the game logic. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        void Update(GU::Engin::Engin& engin, const float &deltaTime) override;


        /****************************************************************//**
        *   @brief  This method draws the current frame. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        void Draw(GU::Engin::Engin& engin, const float &deltaTime) override;


        virtual ~ClientPlayState();
    protected:
    private:
};

#endif // CLIENTPLAYSTATE_H
