#include "Events/Listeners/MusicListener.h"
#include "Events/PlayMusic.h"
#include <memory>
#include <iostream>
#include "Events/Id.h"
#include "Events/MusicVolumeChanged.h"
#include "Settings.h"

sf::Music MusicListener::music;

MusicListener::MusicListener()
{
    //ctor
    music.setLoop(true);
    music.setVolume(255);
}

void MusicListener::OnEvent(Evt::EventPtr event)
{

    switch(event->id)
    {
        case EventId::PLAY_MUSIC:
        {
            std::shared_ptr<PlayMusic> temp =  std::dynamic_pointer_cast<PlayMusic>(event);
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
            int volume = Settings::inst().musicSettings->getVolume();
            music.setVolume(volume);
        }
        break;
    }





}

MusicListener::~MusicListener()
{
    //dtor
}
