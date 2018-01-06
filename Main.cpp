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
#include <boost/program_options.hpp>

#include <sstream>

#ifndef MAJOR_VERSION
    #define MAJOR_VERSION 1
#endif // MAJOR_VERSION

int main(int argc, char* argv[])
{

    std::stringstream ss;
    ss << MAJOR_VERSION << " " << ".0.0.0";

    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("version", MAJOR_VERSION + ".0.0.0")
        ("help", "produce help message");


    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).run(), vm);
    boost::program_options::notify(vm);


    if (vm.count("help"))
    {
        std::cout << desc << "\n";
        return 1;
    }

    boost::log::sources::severity_logger< logging::trivial::severity_level > lg;

//    BOOST_LOG_SEV(lg, logging::trivial::trace) << "A trace severity message";
//    BOOST_LOG_SEV(lg, logging::trivial::debug) << "A debug severity message";
//    BOOST_LOG_SEV(lg, logging::trivial::info) << "An informational severity message";
//    BOOST_LOG_SEV(lg, logging::trivial::warning) << "A warning severity message";
//    BOOST_LOG_SEV(lg, logging::trivial::error) << "An error severity message";
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

    try
    {
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
    catch(...)
    {

    }

}
