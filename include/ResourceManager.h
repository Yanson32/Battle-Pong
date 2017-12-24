#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include "Resource Holder.h"
#include <SFML/Audio/SoundBuffer.hpp>

namespace sf
{
    //class SoundBuffer;
    class String;
}

namespace ResourceManager
{
    extern ResourceHolder<sf::SoundBuffer, sf::String> sound;
}
#endif // RESOURCEMANAGER_H
