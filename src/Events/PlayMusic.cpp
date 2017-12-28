#include "Events/PlayMusic.h"
#include "Events/Id.h"

PlayMusic::PlayMusic(const sf::String &musicFile): EventBase(EventId::PLAY_MUSIC), file(musicFile)
{
    //ctor
}

PlayMusic::~PlayMusic()
{
    //dtor
}
