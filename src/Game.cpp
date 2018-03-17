#include "Game.h"
#include "Events/EventManager.h"
#include <memory>
#include "Events/PlayMusic.h"
#include "Events/Listeners/BallCollisionListener.h"
#include "Events/Id.h"
#include "Events/Listeners/LeftPaddleGoalListener.h"
Game::Game(): GU::Engin::Engin(),
GU::Evt::Manager()
{

}
