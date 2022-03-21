#include "Resources/ResourceManager.h"


namespace ResourceManager
{
    ResourceHolder<sf::SoundBuffer, soundId> sound;
    ResourceHolder<sf::Font, sf::String> font;
    ResourceHolder<sf::Music, musicId> music;
    ResourceHolder<sf::Texture, textureId> texture;
}
