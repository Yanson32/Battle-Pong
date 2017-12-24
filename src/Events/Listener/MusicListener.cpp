#include "Events/Listeners/MusicListener.h"
#include "Events/PlayMusic.h"
#include <memory>
#include <iostream>

sf::Music MusicListener::music;

MusicListener::MusicListener()
{
    //ctor
    music.setLoop(true);
}

void MusicListener::OnEvent(Evt::EventPtr event)
{
    std::cout << "Music Listener" << std::endl;


    std::shared_ptr<PlayMusic> temp =  std::dynamic_pointer_cast<PlayMusic>(event);
    if(temp)
    {
        if(music.openFromFile(temp->file))
        {
            music.play();
            //music.setVolume(100);
        }
        else
        {
            std::cout << "Unable to open music file " << std::endl;
        }

    }
    else
    {
        std::cout << "Cast failes MusicListener::OnEvent" << std::endl;
    }

}

MusicListener::~MusicListener()
{
    //dtor
}
