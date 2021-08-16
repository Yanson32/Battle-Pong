#ifndef SFMLFUNCTIONS_H
#define SFMLFUNCTIONS_H
#include <SFML/System/String.hpp>
#include <SFML/Window/Keyboard.hpp>
int toInt(const sf::String num);
sf::String toString(const sf::Keyboard::Key &key);
sf::Keyboard::Key toKey(const sf::String &key);
#endif // SFMLFUNCTIONS_H
