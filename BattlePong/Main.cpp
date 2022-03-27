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
    //Enable random numbers
    srand (time(NULL));
    
    //Retrieving the public ip address can take a while, especially if there is no internet connection.
    //So we do it in a thread.
    std::thread ipThread([&](){Settings::publicIp = sf::IpAddress::getPublicAddress().toString();});
    ipThread.detach();

    //Create the games window
    sf::RenderWindow window(sf::VideoMode(Settings::dimensions.x, Settings::dimensions.y),Settings::title); 

    //Create tgui object
    tgui::Gui gui;
    gui.setTarget(window);
    
    //Load tgui theme
    ResourceManager::loadTheme("Black");
    
    //Create the games frame
    std::shared_ptr<PongFrame> frame(new PongFrame(window.getView().getSize()));
    
    //Set the debug draw class 
    DebugDraw debugDraw(*frame->world.get());
    frame->world->SetDebugDraw(&debugDraw);

    //Handle program options
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

    
    

    //Create game engin
    Game engin;
   
    
    //Create first GameState instance 
    engin.Push<IntroState>(frame, engin, window, debugDraw, gui);

    //Start the music
    EventManager::inst().Post<GU::Evt::PlayMusic>("Zombies");
   
    //Create clock for game engin 
    sf::Clock timer;
    const sf::Time deltaTime = sf::seconds(1.0f / 60.0f);
    sf::Time accumulator = sf::seconds(0);
    
    try
    {
        while (engin.IsRunning())
        {
            accumulator += timer.restart();
            
	    //Handle any events  
	    engin.HandleEvents(deltaTime.asSeconds(), frame);
            
	    //Update the game logic 
	    while(accumulator.asSeconds() >= deltaTime.asSeconds())
            {
                engin.Update(deltaTime.asSeconds(), frame);
                accumulator -= deltaTime;
            }
            
	    //Draw a frame 
	    engin.Draw(deltaTime.asSeconds(), frame);
        }
    }
    catch(...)
    {
    
    }

}
