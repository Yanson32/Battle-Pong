#include "Events/PlaySound.h"
#include "Events/Id.h"

PlaySound::PlaySound(const sf::String &newId): EventBase(EventId::PLAY_SOUND), soundId(newId)
{
    //ctor
}

PlaySound::~PlaySound()
{
    //dtor
}
