#include "States/HostPlayState.h"
#include "Settings.h"
HostPlayState::HostPlayState(GU::Engin::Engin& newEngin):
PlayState::PlayState(newEngin, stateId::HOST_PLAY_STATE)
{
    //ctor
}

void HostPlayState::Init()
{
    PlayState::Init();
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
void HostPlayState::HandleEvents(GU::Engin::Engin& newEngin, const float &deltaTime)
{
    PlayState::HandleEvents(newEngin, deltaTime);

}


/****************************************************************//**
*   @brief  This method updates the game logic. This should be
*           called once per frame.
*   @param  engin A reference to an Engin::Engin object.
*           This is the main game object.
********************************************************************/
void HostPlayState::Update(GU::Engin::Engin& engin, const float &deltaTime)
{
    PlayState::Update(engin, deltaTime);
}


/****************************************************************//**
*   @brief  This method draws the current frame. This should be
*           called once per frame.
*   @param  engin A reference to an Engin::Engin object.
*           This is the main game object.
********************************************************************/
void HostPlayState::Draw(GU::Engin::Engin& engin, const float &deltaTime)
{
    PlayState::Draw(engin, deltaTime);
}

void HostPlayState::sfEvent(GU::Engin::Engin& engin, const sf::Event &event)
{

}

void HostPlayState::guEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event)
{

}

HostPlayState::~HostPlayState()
{
    //dtor
}
