#ifndef BALLCOLLISIONLISTENER_H
#define BALLCOLLISIONLISTENER_H
#include <GameUtilities/Event/Listener.h>

class BallCollisionListener: public Evt::Listener
{
    public:
        BallCollisionListener();
        void OnEvent(Evt::EventPtr event);
        virtual ~BallCollisionListener();
    protected:
    private:
};

#endif // BALLCOLLISIONLISTENER_H
