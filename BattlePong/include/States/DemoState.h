#ifndef DEMOSTATE_H
#define DEMOSTATE_H
#include <GameUtilities/Engin/Frame.h>
#include "States/StateBase.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Box2D/DebugDraw.h"
#include <TGUI/TGUI.hpp>

class DemoState: public StateBase
{
    public:
        DemoState(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow, DebugDraw &debugDraw, tgui::Gui &newGui);
        virtual ~DemoState();
    protected:
    private:
};

#endif // DEMOSTATE_H
