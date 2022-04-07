#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
/**********************************************************//**
*   @author Wayne J Larson Jr.
*   @date   12/28/17
*   @brief  This file defines several ResourceHolder objects.
*           These objects hold game resources. Game resource
*           should only be loaded once and the Resource holders
*           help to make sure that happens.
**************************************************************/

#include "Resource Holder.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/Music.hpp>
#include "Resources/SoundId.h"
#include "Resources/MusicId.h"
#include "Resources/TextureId.h"
#include "Settings.h"
#include "GameUtilities/Core/String.h"
#include <filesystem>

class ResourceManager
{

    public:
      ResourceManager();
      static void remove(const textureId &texture);
	    static void loadSound(const soundId &sound, const std::string &name);
	    static bool isLoaded(const soundId &sound);
      static sf::SoundBuffer& get(const soundId &sound);
      static void remove(const soundId &sound);
	    static bool isLoaded(const textureId &texture);
	    static void loadBackground(const std::string &name);
	    static void loadTexture(const textureId &texture, const std::string &name);
      static sf::Texture& get(const textureId  &texture);
	    static bool loadMusic(const std::string &music);
      static void loadTheme(const std::string &name);
      static sf::Music& getMusic();
      static void setPath(const std::filesystem::path &path);
      static std::filesystem::path getPath();
	    virtual ~ResourceManager();
    private:
        static std::filesystem::path m_path;

        /**********************************************************//**
        *   @brief  The sound ResourceManager object holds sf::SoundBuffer
        *           objects.
        **************************************************************/
        static ResourceHolder<sf::SoundBuffer, soundId> m_sound;


        /**********************************************************//**
        *   @brief  The sound ResourceManager object holds sf::SoundBuffer
        *           objects.
        **************************************************************/
        static ResourceHolder<sf::Font, sf::String> m_font;


        /**********************************************************//**
        *   @brief  The texture ResourceManager object holds sf::Texture
        *           objects.
        **************************************************************/
        static ResourceHolder<sf::Texture, textureId> m_texture;
        static sf::Music m_music;
};
#endif // RESOURCEMANAGER_H
