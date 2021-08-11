#include "States/DemoState.h"
#include "States/Id.h"

DemoState::DemoState(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow, std::shared_ptr<Frame> newFrame): StateBase::StateBase(newEngin, newWindow, newFrame, stateId::DEMO_STATE)
{
    //ctor
}

DemoState::~DemoState()
{
    //dtor
}
