#include "States/DemoState.h"
#include "States/Id.h"

DemoState::DemoState(GU::Engin::Engin& newEngin): StateBase::StateBase(newEngin, stateId::DEMO_STATE)
{
    //ctor
}

DemoState::~DemoState()
{
    //dtor
}
