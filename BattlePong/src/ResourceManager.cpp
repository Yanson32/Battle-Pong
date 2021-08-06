#include "ResourceManager.h"


namespace ResourceManager
{
    ResourceHolder<sf::SoundBuffer, soundId> sound;
    ResourceHolder<sf::Font, sf::String> font;
    ResourceHolder<sf::Music, sf::String> music;
}
