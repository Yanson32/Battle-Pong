#include "States/SingleplayerState.h"
#include "Macros.h"

SingleplayerState::SingleplayerState(GU::Engin::Engin& newEngin): PlayState(newEngin)
{
    //ctor
}

void SingleplayerState::sfEvent(GU::Engin::Engin& engin, const sf::Event &event)
{
    UNUSED(engin);
    UNUSED(event);
}

void SingleplayerState::handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event)
{
    UNUSED(engin);
    UNUSED(event);
}

SingleplayerState::~SingleplayerState()
{
    //dtor
}
