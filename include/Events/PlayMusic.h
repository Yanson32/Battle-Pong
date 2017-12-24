#ifndef PLAYMUSIC_H
#define PLAYMUSIC_H
#include "Events/EventBase.h"
#include <SFML/System/String.hpp>

class PlayMusic: public EventBase
{
    public:
        PlayMusic(const sf::String &musicFile);
        sf::String file;
        virtual ~PlayMusic();
};

#endif // PLAYMUSIC_H
