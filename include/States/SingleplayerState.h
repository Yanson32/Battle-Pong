#ifndef SINGLEPLAYERSTATE_H
#define SINGLEPLAYERSTATE_H
#include "States/PlayState.h"

class SingleplayerState: public PlayState
{
    public:
        SingleplayerState(GU::Engin::Engin& newEngin);
        void sfEvent(GU::Engin::Engin& engin, const sf::Event &event);
        void guEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event);
        virtual ~SingleplayerState();
    protected:
    private:
};

#endif // SINGLEPLAYERSTATE_H
