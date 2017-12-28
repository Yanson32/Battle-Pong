#include "Game.h"
#include "Events/EventManager.h"
#include <memory>
#include "Events/PlayMusic.h"
#include "Events/Listeners/BallCollisionListener.h"
#include "Events/Id.h"
#include "Events/Listeners/LeftPaddleGoalListener.h"
Game::Game(): Engin::Engin(),
Evt::Manager()
{

}
