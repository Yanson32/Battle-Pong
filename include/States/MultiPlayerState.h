#ifndef MULTIPLAYERSTATE_H
#define MULTIPLAYERSTATE_H

#include "States/PlayState.h"

class MultiPlayerState: public PlayState
{
    public:
        MultiPlayerState(Engin::Engin& engin,
                        const std::string ipAddress = "",
                        const std::string port = "",
                        const bool host = true);

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
        virtual ~MultiPlayerState();
    protected:
    private:
};

#endif // MULTIPLAYERSTATE_H
