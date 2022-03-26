#include "States/IntroState.h"
#include "Events/Events.h"
//#include <Box2D/Box2D.h>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "Game.h"
#include "Events/Events.h"

#include <SFML/Audio/Music.hpp>

#include "Resources/ResourceManager.h"
#include "Resources/ResourceFunctions.h"
#include <boost/program_options.hpp>

#include <sstream>
#include <time.h>

#ifndef MAJOR_VERSION
    #define MAJOR_VERSION 1
#endif // MAJOR_VERSION

#ifndef BOOST_LOG_DYN_LINK
    #define BOOST_LOG_DYN_LINK
#endif

#include "config.h"
#include <GameUtilities/Core/String.h>
#include <GameUtilities/Engin/Frame.h>

#include "Settings.h"
#include "Objects/PongFrame.h"
#include "Box2D/DebugDraw.h"
#include <thread>

#include "SFMLFunctions.h"
int main(int argc, char* argv[])
{
    //Retrieving the public ip address can take a while, especially if there is no internet connection.
    //So we do it in a thread.
    std::thread ipThread([&](){Settings::publicIp = sf::IpAddress::getPublicAddress().toString();});
    ipThread.detach();

    
    sf::RenderWindow window(sf::VideoMode(Settings::dimensions.x, Settings::dimensions.y),Settings::title); 

    tgui::Gui gui;
    gui.setTarget(window);
    std::shared_ptr<PongFrame> frame(new PongFrame(window.getView().getSize()));
    
    srand (time(NULL));

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

    //boost::log::sources::severity_logger< logging::trivial::severity_level > lg;
    
    //Load tgui theme
    ResourceManager::loadTheme("Black");
    
    sf::Clock timer;
    const sf::Time deltaTime = sf::seconds(1.0f / 60.0f);
    sf::Time accumulator = sf::seconds(0);

	Game engin;
    
    DebugDraw debugDraw(*frame->world.get());
    frame->world->SetDebugDraw(&debugDraw);
	engin.Push<IntroState>(frame, engin, window, debugDraw, gui);
	
	
        //Need to call event manager play sound
        EventManager::inst().Post<GU::Evt::PlayMusic>("Zombies");
    try
    {
        while (engin.IsRunning())
        {
            accumulator += timer.restart();
            engin.HandleEvents(deltaTime.asSeconds(), frame);
            while(accumulator.asSeconds() >= deltaTime.asSeconds())
            {
                engin.Update(deltaTime.asSeconds(), frame);
                accumulator -= deltaTime;
            }
            engin.Draw(deltaTime.asSeconds(), frame);
        }
    }
    catch(...)
    {

    }

}
