#ifndef DEMOSTATE_H
#define DEMOSTATE_H
#include "States/StateBase.h"
#include <SFML/Graphics/RenderWindow.hpp>

class DemoState: public StateBase
{
    public:
        DemoState(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow);
        virtual ~DemoState();
    protected:
    private:
};

#endif // DEMOSTATE_H
