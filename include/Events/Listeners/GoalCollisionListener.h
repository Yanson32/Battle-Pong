#ifndef GOALCOLLISION_LISTENER_H
#define GOALCOLLISION_LISTENER_H
#include <GameUtilities/Event/Listener.h>

class GoalCollisionListener: public GU::Evt::Listener
{
    public:
        GoalCollisionListener();
        virtual void OnEvent(GU::Evt::EventPtr event) override;
        virtual ~GoalCollisionListener();
    protected:
    private:
};

#endif // GOALCOLLISION_H
