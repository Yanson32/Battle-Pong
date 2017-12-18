#include "States/StateBase.h"
#include "Settings.h"

sf::RenderWindow StateBase::window(Settings::inst().getWindowSettings().getVideoMode(), Settings::inst().getTitle());
std::unique_ptr<b2World> StateBase::world(new b2World(b2Vec2(0, -9.8)));

StateBase::StateBase(): Engin::GameState()
{

}

StateBase::~StateBase()
{

}
