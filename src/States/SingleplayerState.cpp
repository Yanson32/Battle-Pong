#include "States/SingleplayerState.h"

SingleplayerState::SingleplayerState(GU::Engin::Engin& newEngin): PlayState(newEngin)
{
    //ctor
}

void SingleplayerState::sfEvent(GU::Engin::Engin& engin, const sf::Event &event)
{

}

void SingleplayerState::guEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event)
{

}

SingleplayerState::~SingleplayerState()
{
    //dtor
}
