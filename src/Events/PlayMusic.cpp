#include "Events/PlayMusic.h"

PlayMusic::PlayMusic(const sf::String &musicFile): EventBase(1), file(musicFile)
{
    //ctor
}

PlayMusic::~PlayMusic()
{
    //dtor
}
