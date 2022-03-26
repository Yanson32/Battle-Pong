#include "Resources/ResourceManager.h"
#include <filesystem>

ResourceHolder<sf::SoundBuffer, soundId> ResourceManager::m_sound;
ResourceHolder<sf::Font, sf::String> ResourceManager::m_font;
ResourceHolder<sf::Texture, textureId> ResourceManager::m_texture;
sf::Music ResourceManager::m_music;

ResourceManager::ResourceManager()
{
    
}


void ResourceManager::loadSound(const soundId &sound, const std::string &name)
{
    //Load title image
    if(!m_sound.isLoaded(sound))
    {
        if(std::filesystem::exists(Settings::SOUNDS_BINARY_DIR))
            m_sound.load(sound, Settings::SOUNDS_BINARY_DIR + name);
        else
            m_sound.load(sound, Settings::SOUNDS_INSTALL_DIR + name);

    }

}


bool ResourceManager::isLoaded(const soundId &sound)
{
    return m_sound.isLoaded(sound);
}


sf::SoundBuffer& ResourceManager::get(const soundId &sound)
{
    return m_sound.get(sound);
}


void ResourceManager::remove(const soundId &sound)
{
    m_sound.remove(sound);
}


bool ResourceManager::loadMusic(const std::string &music)
{
        if(std::filesystem::exists(Settings::SOUNDS_BINARY_DIR))
	{
            m_music.openFromFile(Settings::MUSIC_BINARY_DIR + music + ".ogg");
	    Settings::currentSong = music;	
	} 
	else
	{
            m_music.openFromFile(Settings::MUSIC_INSTALL_DIR + music + ".ogg");
	    Settings::currentSong = music;
	}

    return true;
}


void ResourceManager::remove(const textureId &texture)
{
    m_texture.remove(texture);
}


sf::Texture& ResourceManager::get(const textureId  &texture)
{
    return m_texture.get(texture);
}


bool ResourceManager::isLoaded(const textureId &texture)
{
    return m_texture.isLoaded(texture);
}


void ResourceManager::loadTexture(const textureId &texture, const std::string &name)
{
    //Load title image
    if(!m_texture.isLoaded(texture))
    {
        if(std::filesystem::exists(Settings::IMAGES_BINARY_DIR))
            m_texture.load(texture, sf::String(Settings::IMAGES_BINARY_DIR + Settings::theme + "/" + name));
        else
            m_texture.load(texture, sf::String(Settings::IMAGES_INSTALL_DIR + Settings::theme + "/" + name));

    }

}


void ResourceManager::loadBackground(const std::string &name)
{

    if(m_texture.isLoaded(textureId::BACKGROUND))
        m_texture.remove(textureId::BACKGROUND);

    //Load title image
    if(!m_texture.isLoaded(textureId::BACKGROUND))
    {
        if(std::filesystem::exists(Settings::BACKGROUNDS_BINARY_DIR))
            m_texture.load(textureId::BACKGROUND, sf::String(Settings::BACKGROUNDS_BINARY_DIR  + name));
        else
            m_texture.load(textureId::BACKGROUND, sf::String(Settings::BACKGROUNDS_INSTALL_DIR  + name));

    }

}


void ResourceManager::loadTheme(const std::string &name)
{
   if(name == "Default")
   {
        tgui::Theme::setDefault(nullptr);
        Settings::theme = name;
   }
   else if(std::filesystem::exists(Settings::THEME_BINARY_DIR))
   {
        tgui::Theme::setDefault(Settings::THEME_BINARY_DIR + name + ".txt");
        Settings::theme = name;
   }
   else
   {
       tgui::Theme::setDefault(Settings::THEME_INSTALL_DIR + name + ".txt");
       Settings::theme = name;
   }

   if(name == "BabyBlue")
           Settings::theme = "Blue";
}


sf::Music& ResourceManager::getMusic()
{
    return m_music;
}


ResourceManager::~ResourceManager()
{
    
}
