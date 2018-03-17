#ifndef PONG_ENGIN_H
#define PONG_ENGIN_H

#include <GameUtilities/Engin/Engin.h>
#include <GameUtilities/Event/Manager.h>


class Game: public GU::Engin::Engin, public GU::Evt::Manager
{
    public:
        Game();
    protected:

    private:

};
#endif
