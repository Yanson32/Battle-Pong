#include "ResourceManager.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Font.hpp>

namespace ResourceManager
{
    ResourceHolder<sf::SoundBuffer, sf::String> sound;
    ResourceHolder<sf::Font, sf::String> font;

}
