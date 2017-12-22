#ifndef PONG_PLAYSTATE_H
#define PONG_PLAYSTATE_H
#include "States/StateBase.h"
#include <memory>
#include "Ball.h"




class PlayState: public StateBase
{
    public:
        PlayState(Engin::Engin& newEngin);
        void HandleEvents(Engin::Engin& newEngin);
        void Update(Engin::Engin& engin);
        void Draw(Engin::Engin& engin);
        ~PlayState();
    private:

};
#endif
