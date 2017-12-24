#ifndef PLAYSOUND_H
#define PLAYSOUND_H
#include <SFML/System/String.hpp>
#include "EventBase.h"

class PlaySound: public EventBase
{
    public:
        PlaySound(const sf::String &newId);
        sf::String soundId;
        virtual ~PlaySound();
    protected:
    private:

};

#endif // PLAYSOUND_H
