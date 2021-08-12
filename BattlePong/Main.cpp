#include "States/IntroState.h"
#include "Events/Events.h"
//#include <Box2D/Box2D.h>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "Game.h"
#include "Events/Events.h"

#include <SFML/Audio/Music.hpp>

#include "Resources/ResourceManager.h"
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

#include "Settings.h"
#include "Objects/Frame.h"
#include "Box2D/DebugDraw.h"

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(Settings::window.dimensions.x, Settings::window.dimensions.y),Settings::window.title); 

    tgui::Gui gui;
    gui.setTarget(window);

    std::shared_ptr<Frame> frame(new Frame(window.getView().getSize()));
    
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
    tgui::Theme::setDefault("Resources/TGUI/Theme/Black.txt");
    
    
    sf::Clock timer;
    const sf::Time deltaTime = sf::seconds(1.0f / 60.0f);
    sf::Time accumulator = sf::seconds(0);

	Game engin;
    
    DebugDraw debugDraw(*frame->world.get());
    frame->world->SetDebugDraw(&debugDraw);
	engin.Push<IntroState>(engin, window, frame, debugDraw);
	EventManager::inst().Post<GU::Evt::PlayMusic>("Resources/Music/Electro_Zombies.ogg");

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
