#ifndef SINGLEPLAYERSTATE_H
#define SINGLEPLAYERSTATE_H
#include "States/PlayState.h"

class SingleplayerState: public PlayState
{
    public:
        SingleplayerState(Engin::Engin& newEngin);
        void sfEvent(Engin::Engin& engin, const sf::Event &event);
        void guEvent(Engin::Engin& engin, Evt::EventPtr event);
        virtual ~SingleplayerState();
    protected:
    private:
};

#endif // SINGLEPLAYERSTATE_H
