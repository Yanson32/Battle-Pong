#ifndef PONG_ENGIN_H
#define PONG_ENGIN_H

#include <GameUtilities/Engin/Engin.h>
#include <GameUtilities/Event/Manager.h>
#include "MusicListener.h"
#include "SoundListener.h"
#include "BallCollisionListener.h"

class Game: public Engin::Engin, public Evt::Manager
{
    public:
        Game();
    protected:

    private:
        MusicListener* musicListener;
        SoundListener* soundListener;
        BallCollisionListener* ballCollisionListener;
};
#endif
