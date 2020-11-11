#ifndef DEMOSTATE_H
#define DEMOSTATE_H
#include "States/StateBase.h"

class DemoState: public StateBase
{
    public:
        DemoState(GU::Engin::Engin& newEngin);
        virtual ~DemoState();
    protected:
    private:
};

#endif // DEMOSTATE_H
