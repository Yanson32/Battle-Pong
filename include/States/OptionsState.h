#ifndef OPTIONSSTATE_H
#define OPTIONSSTATE_H
#include "States/StateBase.h"


class OptionsState: public StateBase
{
    public:
        OptionsState(Engin::Engin& engin);
        virtual void HandleEvents(Engin::Engin& newEngin) override;
        virtual void Update(Engin::Engin& engin) override;
        virtual void Draw(Engin::Engin& engin) override;
        virtual ~OptionsState();
    protected:
    private:
    void onControlsPressed();
    void onBackPressed();

};

#endif // OPTIONSSTATE_H
