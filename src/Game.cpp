#include "Game.h"
#include "Events/EventManager.h"
#include <memory>
#include "Events/PlayMusic.h"
#include "Events/Listeners/BallCollisionListener.h"

Game::Game(): Engin::Engin(),
Evt::Manager(),
musicListener(new MusicListener()),
soundListener(new SoundListener),
ballCollisionListener(new BallCollisionListener)
{
    EventManager::inst().RegisterListener(std::move(musicListener), 1);
    EventManager::inst().RegisterListener(std::move(soundListener), 2);
    EventManager::inst().RegisterListener(std::move(ballCollisionListener), 3);
}
