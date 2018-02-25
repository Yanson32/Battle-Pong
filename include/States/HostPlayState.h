#ifndef HOSTPLAYSTATE_H
#define HOSTPLAYSTATE_H
#include "States/PlayState.h"
#include "Server.h"
#include <memory>

class HostPlayState: public PlayState
{
    public:
        HostPlayState(Engin::Engin& newEngin, std::unique_ptr<Server> serverPtr);
                virtual void Init() override;
        virtual void Clean() override;

        /****************************************************************//**
        *   @brief  This method handles input such as user input and events.
        *           This should be called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        void HandleEvents(Engin::Engin& newEngin, const int &deltaTime);


        /****************************************************************//**
        *   @brief  This method updates the game logic. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        void Update(Engin::Engin& engin, const int &deltaTime);


        /****************************************************************//**
        *   @brief  This method draws the current frame. This should be
        *           called once per frame.
        *   @param  engin A reference to an Engin::Engin object.
        *           This is the main game object.
        ********************************************************************/
        void Draw(Engin::Engin& engin, const int &deltaTime);
        virtual ~HostPlayState();
    protected:
    private:
};

#endif // HOSTPLAYSTATE_H
