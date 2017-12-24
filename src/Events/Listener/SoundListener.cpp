#include "Events/Listeners/SoundListener.h"
#include "ResourceManager.h"
#include <iostream>
#include <SFML/System/String.hpp>
#include "Events/PlaySound.h"
//sf::Sound SoundListener::listenerSound;

SoundListener::SoundListener()
{
    //ctor
}

void SoundListener::OnEvent(Evt::EventPtr event)
{
    std::shared_ptr<PlaySound> temp =  std::dynamic_pointer_cast<PlaySound>(event);

    if(temp && ResourceManager::sound.isLoaded(temp->soundId))
    {
        listenerSound.setBuffer(ResourceManager::sound.get(temp->soundId));
        listenerSound.play();
    }
}

SoundListener::~SoundListener()
{
    //dtor
    listenerSound.resetBuffer();
}
