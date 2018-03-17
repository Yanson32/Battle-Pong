#ifndef CLIENTPLAYSTATE_H
#define CLIENTPLAYSTATE_H

#include "States/PlayState.h"
#include "Client.h"
#include <iostream>
#include <memory>

class ClientPlayState: public PlayState
{
    public:
        ClientPlayState(GU::Engin::Engin& newEngin, std::unique_ptr<Client> newClient);

        virtual void Init() override;
        virtual void Clean() override;

        /****************************************************************//**
        *   @brief  This method handles input such as user input and events.
        *           This should be called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        void HandleEvents(GU::Engin::Engin& newEngin, const int &deltaTime);


        /****************************************************************//**
        *   @brief  This method updates the game logic. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        void Update(GU::Engin::Engin& engin, const int &deltaTime);


        /****************************************************************//**
        *   @brief  This method draws the current frame. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        void Draw(GU::Engin::Engin& engin, const int &deltaTime);


        virtual ~ClientPlayState();
    protected:
    private:
        std::unique_ptr<Client> client = nullptr;
};

#endif // CLIENTPLAYSTATE_H
