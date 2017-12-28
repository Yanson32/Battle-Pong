#ifndef RIGHTPADDLEGOALLISTENER_H
#define RIGHTPADDLEGOALLISTENER_H
#include <GameUtilities/Event/Listener.h>


class RightPaddleGoalListener: public Evt::Listener
{
    public:
        RightPaddleGoalListener();
        virtual void OnEvent(Evt::EventPtr event) override;
        virtual ~RightPaddleGoalListener();
    protected:
    private:
};

#endif // RIGHTPADDLEGOALLISTENER_H
