#include "Resources/ResourceManager.h"

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
  std::filesystem::path path = m_path;
  path += std::filesystem::path("/Music/");

  if(std::filesystem::exists(path))
	{
      m_music.openFromFile(path.string() + music + ".ogg");
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
            m_texture.load(texture, sf::String(path.string() + Settings::theme + "/" + name));

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
        Settings::theme = name;
   }
   else if(std::filesystem::exists(path))
   {
        tgui::Theme::setDefault(path.string() + name + ".txt");
        Settings::theme = name;
   }

   if(name == "BabyBlue")
           Settings::theme = "Blue";
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
