#include "States/IntroState.h"
#include "Events/PlayMusic.h"
#include <Box2D/Box2D.h>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "Game.h"
#include "Events/Listeners/MusicListener.h"
#include "Events/EventManager.h"
#include "Events/MusicVolumeChanged.h"
#include "Events/SoundVolumeChanged.h"

#include <SFML/Audio/Music.hpp>

#include "ResourceManager.h"
#include "Logging.h"


int main()
{









    init();


    using namespace logging::trivial;
    src::severity_logger< severity_level > lg;

    BOOST_LOG_SEV(lg, trace) << "A trace severity message";
    BOOST_LOG_SEV(lg, debug) << "A debug severity message";
    BOOST_LOG_SEV(lg, info) << "An informational severity message";
    BOOST_LOG_SEV(lg, warning) << "A warning severity message";
    BOOST_LOG_SEV(lg, error) << "An error severity message";
    //BOOST_LOG_SEV(lg, fatal) << "A fatal severity message";
//    ResourceManager::sound.load("Message Sound", "/home/me/Desktop/Pong/Build/Resources/Sounds/tone1.ogg");
//    ResourceManager::sound.load("Button Sound", "/home/me/Desktop/Pong/Build/Resources/Sounds/tone1.ogg");
//    ResourceManager::sound.load("List Box Selected Sound", "/home/me/Desktop/Pong/Build/Resources/Sounds/tone1.ogg");
//    ResourceManager::sound.load("Edit Box Sound", "/home/me/Desktop/Pong/Build/Resources/Sounds/tone1.ogg");
//    ResourceManager::sound.load("Ball Sound", "/home/me/Desktop/Pong/Build/Resources/Sounds/tone1.ogg");
//    ResourceManager::font.load("Header Font", "/home/me/Desktop/Pong/Build/Resources/Fonts/caviar-dreams/CaviarDreams.ttf");

//    ResourceManager::sound.remove("Message Sound");
//    ResourceManager::sound.remove("Button Sound");
//    ResourceManager::sound.remove("List Box Selected Sound");
//    ResourceManager::sound.remove("Edit Box Sound");
//    ResourceManager::sound.remove("Ball Sound");
//    ResourceManager::font.remove("Header Font");

    sf::Clock timer;
    const sf::Time deltaTime = sf::seconds(1.0f / 60.0f);
    sf::Time accumulator = sf::seconds(0);

	Game engin;
	engin.Push<IntroState>(engin);
	EventManager::inst().Post<PlayMusic>("/home/me/Desktop/Pong/Build/Resources/Music/Electro_Zombies.ogg");
	EventManager::inst().Post<MusicVolumeChanged>();
	EventManager::inst().Post<SoundVolumeChanged>();

	while (engin.IsRunning())
	{
        accumulator += timer.restart();
        engin.HandleEvents(deltaTime.asSeconds());
        while(accumulator.asSeconds() >= deltaTime.asSeconds())
        {
            engin.Update(deltaTime.asSeconds());
            accumulator -= deltaTime;
        }
		engin.Draw(deltaTime.asSeconds());
	}

}
