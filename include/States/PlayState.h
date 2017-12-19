#ifndef PONG_PLAYSTATE_H
#define PONG_PLAYSTATE_H
#include "States/StateBase.h"
#include "Ball.h"
#include "Wall.h"
#include <memory>

class PlayState: public StateBase
{
    public:
        PlayState();
        void HandleEvents(Engin::Engin& engin);
        void Update(Engin::Engin& engin);
        void Draw(Engin::Engin& engin);
        ~PlayState();
    private:
        Ball ball;
        Wall* ground = nullptr;
        Wall* celing = nullptr;
        Wall* leftWall = nullptr;
        Wall* RightWall = nullptr;
};
#endif
