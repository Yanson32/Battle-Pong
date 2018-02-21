#ifndef SINGLEPLAYERSTATE_H
#define SINGLEPLAYERSTATE_H
#include "States/PlayState.h"

class SingleplayerState: public PlayState
{
    public:
        SingleplayerState(Engin::Engin& newEngin);
        virtual ~SingleplayerState();
    protected:
    private:
};

#endif // SINGLEPLAYERSTATE_H
