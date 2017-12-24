#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include "Resource Holder.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/String.hpp>

namespace ResourceManager
{
    extern ResourceHolder<sf::SoundBuffer, sf::String> sound;
    extern ResourceHolder<sf::Font, sf::String> font;
}
#endif // RESOURCEMANAGER_H
