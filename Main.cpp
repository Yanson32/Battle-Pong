#include "States/IntroState.h"
#include "Events/PlayMusic.h"
#include <iostream>
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

#define BOOST_LOG_DYN_LINK

#include <boost/move/utility_core.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include "Events/EventManager.h"

namespace logging = boost::log;
namespace src = boost::log::sources;

void logInit()
{
    logging::add_file_log("Pong.log");
}

int main()
{
	logInit();
    src::logger lg;
    BOOST_LOG(lg) << "Blah";
    ResourceManager::sound.load("Message Sound", "/home/me/Desktop/Pong/Build/Resources/Sounds/tone1.ogg");
    ResourceManager::sound.load("Button Sound", "/home/me/Desktop/Pong/Build/Resources/Sounds/tone1.ogg");
    ResourceManager::sound.load("List Box Selected Sound", "/home/me/Desktop/Pong/Build/Resources/Sounds/tone1.ogg");
    ResourceManager::sound.load("Edit Box Sound", "/home/me/Desktop/Pong/Build/Resources/Sounds/tone1.ogg");
    ResourceManager::sound.load("Ball Sound", "/home/me/Desktop/Pong/Build/Resources/Sounds/tone1.ogg");
    ResourceManager::font.load("Header Font", "/home/me/Desktop/Pong/Build/Resources/Fonts/caviar-dreams/CaviarDreams.ttf");
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
        engin.HandleEvents();
        while(accumulator.asSeconds() >= deltaTime.asSeconds())
        {
            engin.Update();
            accumulator -= deltaTime;
        }
		engin.Draw();
	}

}
