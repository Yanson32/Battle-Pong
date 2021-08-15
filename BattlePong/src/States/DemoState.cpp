#include "States/DemoState.h"
#include "States/StateId.h"

DemoState::DemoState(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow, std::shared_ptr<Frame> newFrame, DebugDraw &debugDraw, tgui::Gui &newGui): StateBase::StateBase(newEngin, newWindow, newFrame, debugDraw, newGui, StateId::DEMO_STATE)
{
    //ctor
}

DemoState::~DemoState()
{
    //dtor
}
