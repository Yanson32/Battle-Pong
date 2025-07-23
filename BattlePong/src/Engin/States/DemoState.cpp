#include "Engin/States/DemoState.h"
#include "Engin/States/StateId.h"

DemoState::DemoState(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow, DebugDraw &debugDraw, tgui::Gui &newGui): StateBase::StateBase(newEngin, newWindow, debugDraw, newGui, StateId::DEMO_STATE)
{
    //ctor
}

DemoState::~DemoState()
{
    //dtor
}
