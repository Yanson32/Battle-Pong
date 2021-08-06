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

namespace ResourceManager
{
    /**********************************************************//**
    *   @brief  The sound ResourceManager object holds sf::SoundBuffer
    *           objects.
    **************************************************************/
    extern ResourceHolder<sf::SoundBuffer, soundId> sound;


    /**********************************************************//**
    *   @brief  The sound ResourceManager object holds sf::SoundBuffer
    *           objects.
    **************************************************************/
    extern ResourceHolder<sf::Font, sf::String> font;


    /**********************************************************//**
    *   @brief  The sound ResourceManager object holds sf::Music
    *           objects.
    **************************************************************/
    extern ResourceHolder<sf::Music, sf::String> music;

}
#endif // RESOURCEMANAGER_H
