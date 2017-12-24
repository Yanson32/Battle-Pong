#ifndef PADDLESTATE_H
#define PADDLESTATE_H
#include "States/StateBase.h"
#include "Settings.h"

class PaddleState: public StateBase
{
    public:
        PaddleState(Engin::Engin& newEngin, tgui::Panel::Ptr newPSettings);
        virtual void HandleEvents(Engin::Engin& newEngin) override;
        virtual void Update(Engin::Engin& engin) override;
        virtual void Draw(Engin::Engin& engin) override;
        virtual ~PaddleState();
    protected:
    private:
        tgui::Panel::Ptr pSettings;
        void onBack();
};

#endif // PADDLESTATE_H
