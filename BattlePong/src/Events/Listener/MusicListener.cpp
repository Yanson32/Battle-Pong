#include "Events/Listeners/MusicListener.h"
#include <memory>
#include "Events/Events.h"
#include "Settings.h"
#include <iostream>

sf::Music MusicListener::music;

MusicListener::MusicListener()
{
    //ctor
    music.setLoop(true);
    music.setVolume(255);
}

void MusicListener::OnEvent(GU::Evt::EventPtr event)
{
    std::cout << "Music Listener" << std::endl;
    switch(event->id)
    {
        case EventId::PLAY_MUSIC:
        {
            std::shared_ptr<GU::Evt::PlayMusic> temp =  std::dynamic_pointer_cast<GU::Evt::PlayMusic>(event);
            if(temp)
            {
                if(music.openFromFile(temp->file))
                {
                    music.play();
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
        break;

        case EventId::MUSIC_VOLUME_CHANGED:
        {
            music.setVolume(tempSettings::music.mVolume);
        }
        break;
    }





}

MusicListener::~MusicListener()
{
    //dtor
}
