#ifndef CHANGESTATE_H
#define CHANGESTATE_H
#include "Events/EventBase.h"
#include "States/Id.h"
#include "Events/Id.h"


class ChangeState: public EventBase
{
    public:
        ChangeState(const stateId newState);
        const stateId state;
        virtual ~ChangeState();
};

#endif // CHANGESTATE_H
