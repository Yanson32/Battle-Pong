#ifndef DEMOSTATE_H
#define DEMOSTATE_H
#include "States/StateBase.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Objects/Frame.h"
#include "Box2D/DebugDraw.h"

class DemoState: public StateBase
{
    public:
        DemoState(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow, std::shared_ptr<Frame> newFrame, DebugDraw &debugDraw);
        virtual ~DemoState();
    protected:
    private:
};

#endif // DEMOSTATE_H
