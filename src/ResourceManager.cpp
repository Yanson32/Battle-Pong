#include "ResourceManager.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/String.hpp>

namespace ResourceManager
{
    ResourceHolder<sf::SoundBuffer, sf::String> sound;

}
