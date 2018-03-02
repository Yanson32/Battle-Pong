#include "States/SingleplayerState.h"

SingleplayerState::SingleplayerState(Engin::Engin& newEngin): PlayState(newEngin)
{
    //ctor
}

void SingleplayerState::sfEvent(Engin::Engin& engin, const sf::Event &event)
{

}

void SingleplayerState::guEvent(Engin::Engin& engin, Evt::EventPtr event)
{

}

SingleplayerState::~SingleplayerState()
{
    //dtor
}
