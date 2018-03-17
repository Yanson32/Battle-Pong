#include "Events/Listeners/SoundListener.h"
#include "ResourceManager.h"
#include <SFML/System/String.hpp>
#include "Events/PlaySound.h"
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

        std::cout << "Play Sound " << std::endl;
        case EventId::PLAY_SOUND:
        {
            std::shared_ptr<PlaySound> temp =  std::dynamic_pointer_cast<PlaySound>(event);

            if(temp && ResourceManager::sound.isLoaded(temp->soundId))
            {
                listenerSound.setBuffer(ResourceManager::sound.get(temp->soundId));
                listenerSound.play();
            }
        }
        break;

        case EventId::SOUND_VOLUME_CHANGED:
        {

            listenerSound.setVolume(Settings::inst().musicSettings->getSoundVolume());
            std::cout << "Sound Volume " << Settings::inst().musicSettings->getSoundVolume() << std::endl;
        }
        break;
    }
}

SoundListener::~SoundListener()
{
    //dtor
    listenerSound.resetBuffer();
}
