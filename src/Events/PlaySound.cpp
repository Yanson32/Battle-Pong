#include "Events/PlaySound.h"

PlaySound::PlaySound(const sf::String &newId): EventBase(2), soundId(newId)
{
    //ctor
}

PlaySound::~PlaySound()
{
    //dtor
}
