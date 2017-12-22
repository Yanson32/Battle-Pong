#ifndef CONTROLSTATE_H
#define CONTROLSTATE_H
#include "States/StateBase.h"

class ControlState: public StateBase
{
    public:
        ControlState(Engin::Engin& newEngin);
        virtual void HandleEvents(Engin::Engin& newEngin) override;
        virtual void Update(Engin::Engin& engin) override;
        virtual void Draw(Engin::Engin& engin) override;
        virtual ~ControlState();
    protected:
    private:
};

#endif // CONTROLSTATE_H

