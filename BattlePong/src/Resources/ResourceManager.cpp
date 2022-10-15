#include "Resources/ResourceManager.h"
#include "Resources/Music/Dreams.h"
#include "Resources/Music/Zombies.h"

ResourceHolder<sf::SoundBuffer, soundId> ResourceManager::m_sound;
ResourceHolder<sf::Font, sf::String> ResourceManager::m_font;
ResourceHolder<sf::Texture, textureId> ResourceManager::m_texture;
sf::Music ResourceManager::m_music;
std::filesystem::path ResourceManager::m_path =  std::filesystem::current_path() += "/Resources";
ResourceManager::ResourceManager()
{

}


void ResourceManager::loadSound(const soundId &sound, const std::string &name)
{
    //Load title image
    if(!m_sound.isLoaded(sound))
    {
        std::filesystem::path path = m_path;
        path += std::filesystem::path("/Sounds/" + name);
        if(std::filesystem::exists(path))
            m_sound.load(sound, path.string());

    }

}

void ResourceManager::loadSound(const soundId &sound, const void* data, const std::size_t &bytes)
{
    if(!m_sound.isLoaded(sound))
    {
        m_sound.load(sound,data, bytes);
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
    if(music == "Dreams")
    {
        m_music.openFromMemory(Dreams_ogg, Dreams_ogg_len);
    }
    else if(music == "Zombies")
    {
        m_music.openFromMemory(Zombies_ogg, Zombies_ogg_len);
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
        std::filesystem::path path = m_path;
        path += std::filesystem::path("/Textures/");
        if(std::filesystem::exists(path))
            m_texture.load(texture, sf::String(path.string() + Settings::currentTheme + "/" + name));

    }

}


void ResourceManager::loadTexture(const textureId &texture, const void* data, const std::size_t &bytes)
{
    if(!m_texture.isLoaded(texture))
    {
        m_texture.load(texture, data, bytes);
    }
}


void ResourceManager::loadBackground(const void* data, const std::size_t &bytes)
{
    if(m_texture.isLoaded(textureId::BACKGROUND))
        m_texture.remove(textureId::BACKGROUND);

    //Load title image
    if(!m_texture.isLoaded(textureId::BACKGROUND))
    {
        m_texture.load(textureId::BACKGROUND, data, bytes); 
    }

}

void ResourceManager::loadBackground(const std::string &name)
{
    if(m_texture.isLoaded(textureId::BACKGROUND))
        m_texture.remove(textureId::BACKGROUND);

    //Load title image
    if(!m_texture.isLoaded(textureId::BACKGROUND))
    {
        std::filesystem::path path = m_path;
        path += std::filesystem::path("/Textures/Backgrounds/");
        if(std::filesystem::exists(path))
            m_texture.load(textureId::BACKGROUND, path.string()  + name);
    }

}


void ResourceManager::loadTheme(const std::string &name)
{
   std::filesystem::path path = m_path;
   path += std::filesystem::path("/TGUI/Theme/");
   if(name == "Default")
   {
        tgui::Theme::setDefault(nullptr);
        Settings::currentTheme = name;
   }
   else if(std::filesystem::exists(path))
   {
        tgui::Theme::setDefault(path.string() + name + ".txt");
        Settings::currentTheme = name;
   }

   loadBackground(name);
}


sf::Music& ResourceManager::getMusic()
{
    return m_music;
}

void ResourceManager::setPath(const std::filesystem::path &path)
{
  m_path = path;
}

std::filesystem::path ResourceManager::getPath()
{
  return m_path;
}


ResourceManager::~ResourceManager()
{

}
