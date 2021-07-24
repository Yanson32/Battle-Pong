#include "Events/Listeners/SoundListener.h"
#include "ResourceManager.h"
#include <SFML/System/String.hpp>
#include "Events/Events.h"
#include "Settings.h"
#include "Events/Id.h"

sf::Sound SoundListener::listenerSound;

SoundListener::SoundListener()
{
    //ctor
    listenerSound.setVolume(255);
}

void SoundListener::OnEvent(GU::Evt::EventPtr event)
{
    switch(event->id)
    {

        case EventId::PLAY_SOUND:
        {
            std::shared_ptr<GU::Evt::PlaySound> temp =  std::dynamic_pointer_cast<GU::Evt::PlaySound>(event);

            if(temp && ResourceManager::sound.isLoaded(temp->soundId))
            {
                listenerSound.setBuffer(ResourceManager::sound.get(temp->soundId));
                listenerSound.play();
            }
        }
        break;

        case EventId::SOUND_VOLUME_CHANGED:
        {

            listenerSound.setVolume(Settings::music.sVolume);
        }
        break;
    }
}

SoundListener::~SoundListener()
{
    //dtor
    listenerSound.resetBuffer();
}
