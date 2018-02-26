#include "States/HostPlayState.h"

HostPlayState::HostPlayState(Engin::Engin& newEngin, std::unique_ptr<Server> serverPtr):
PlayState::PlayState(newEngin),
server(std::move(serverPtr))
{
    //ctor
}

void HostPlayState::Init()
{
    PlayState::Init();

    server->init();
}
void HostPlayState::Clean()
{
    PlayState::Clean();
}

/****************************************************************//**
*   @brief  This method handles input such as user input and events.
*           This should be called once per frame.
*   @param  engin A reference to an Engin::Engin object.
*           This is the main game object.
********************************************************************/
void HostPlayState::HandleEvents(Engin::Engin& newEngin, const int &deltaTime)
{
    PlayState::HandleEvents(newEngin, deltaTime);
}


/****************************************************************//**
*   @brief  This method updates the game logic. This should be
*           called once per frame.
*   @param  engin A reference to an Engin::Engin object.
*           This is the main game object.
********************************************************************/
void HostPlayState::Update(Engin::Engin& engin, const int &deltaTime)
{
    PlayState::Update(engin, deltaTime);
}


/****************************************************************//**
*   @brief  This method draws the current frame. This should be
*           called once per frame.
*   @param  engin A reference to an Engin::Engin object.
*           This is the main game object.
********************************************************************/
void HostPlayState::Draw(Engin::Engin& engin, const int &deltaTime)
{
    PlayState::Draw(engin, deltaTime);
}

HostPlayState::~HostPlayState()
{
    //dtor
}
