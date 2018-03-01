#include "Events/ChangeState.h"


ChangeState::ChangeState(const stateId newState):
EventBase(EventId::CHANGE_STATE),
state(newState)
{
    //ctor
}

ChangeState::~ChangeState()
{
    //dtor
}
