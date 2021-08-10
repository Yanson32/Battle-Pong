#include "States/DemoState.h"
#include "States/Id.h"

DemoState::DemoState(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow): StateBase::StateBase(newEngin, newWindow, stateId::DEMO_STATE)
{
    //ctor
}

DemoState::~DemoState()
{
    //dtor
}
