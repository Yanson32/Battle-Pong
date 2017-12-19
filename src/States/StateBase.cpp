#include "States/StateBase.h"
#include "Settings.h"

sf::RenderWindow StateBase::window(Settings::inst().getWindowSettings().getVideoMode(), Settings::inst().getTitle());
std::unique_ptr<b2World> StateBase::world(new b2World(b2Vec2(0, 0)));
tgui::Gui StateBase::gui(window);

StateBase::StateBase(): Engin::GameState()
{
    world->SetDebugDraw(&debugDraw);
}


//void StateBase::Update(Engin::Engin& engin)
//{
//    if(!IsPaused())
//    {
//        world->Step(timeStep, velocityIterations, positionIterations);
//    }
//}



StateBase::~StateBase()
{

}
