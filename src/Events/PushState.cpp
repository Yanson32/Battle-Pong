#include "Events/PushState.h"
#include "Events/Id.h"

PushState::PushState(): EventBase::EventBase(EventId::PUSH_STATE)
{
    //ctor
}

PushState::~PushState()
{
    //dtor
}
