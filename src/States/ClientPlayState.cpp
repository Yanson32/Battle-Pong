#include "States/ClientPlayState.h"
#include "Events/EventManager.h"
#include "States/Id.h"
#include "Settings.h"

ClientPlayState::ClientPlayState(GU::Engin::Engin& newEngin):
PlayState::PlayState(newEngin, stateId::CLIENT_PLAY_STATE)
{
    //ctor
}

void ClientPlayState::Init()
{
    PlayState::Init();
    Settings::inst().clientSettings->init();
}

void ClientPlayState::Clean()
{
    PlayState::Clean();
}

/****************************************************************//**
*   @brief  This method handles input such as user input and events.
*           This should be called once per frame.
*   @param  engin A reference to an Engin::Engin object.
*           This is the main game object.
********************************************************************/
void ClientPlayState::HandleEvents(GU::Engin::Engin& newEngin, const float &deltaTime)
{
    PlayState::HandleEvents(newEngin, deltaTime);
}


/****************************************************************//**
*   @brief  This method updates the game logic. This should be
*           called once per frame.
*   @param  engin A reference to an Engin::Engin object.
*           This is the main game object.
********************************************************************/
void ClientPlayState::Update(GU::Engin::Engin& engin, const float &deltaTime)
{
    PlayState::Update(engin, deltaTime);
}


/****************************************************************//**
*   @brief  This method draws the current frame. This should be
*           called once per frame.
*   @param  engin A reference to an Engin::Engin object.
*           This is the main game object.
********************************************************************/
void ClientPlayState::Draw(GU::Engin::Engin& engin, const float &deltaTime)
{
    PlayState::Draw(engin, deltaTime);
}

ClientPlayState::~ClientPlayState()
{
    //dtor
}
