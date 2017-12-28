#ifndef LEFTPADDLEGOALLISTENER_H
#define LEFTPADDLEGOALLISTENER_H
#include <GameUtilities/Event/Listener.h>

class LeftPaddleGoalListener: public Evt::Listener
{
    public:
        LeftPaddleGoalListener();
        virtual void OnEvent(Evt::EventPtr event) override;
        virtual ~LeftPaddleGoalListener();
    protected:
    private:
};

#endif // LEFTPADDLEGOALLISTENER_H
