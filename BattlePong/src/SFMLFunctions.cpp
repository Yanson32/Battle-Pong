#include "SFMLFunctions.h"
#include <string>
#include <iostream>
#include <SFML/Window/Keyboard.hpp>

int toInt(const sf::String num)
{
    std::string temp = num.toAnsiString();

    return std::atoi(num.toAnsiString().c_str());
}


sf::String toString(const sf::Keyboard::Key &key)
{

    if(key == sf::Keyboard::Key::A)
        return sf::String("A");
    else if(key == sf::Keyboard::Key::B)
        return sf::String("B");
    else if(key == sf::Keyboard::Key::C)
        return sf::String("C");
    else if(key == sf::Keyboard::Key::D)
        return sf::String("D");
    else if(key == sf::Keyboard::Key::E)
        return sf::String("E");
    else if(key == sf::Keyboard::Key::F)
        return sf::String("F");
    else if(key == sf::Keyboard::Key::G)
        return sf::String("G");
    else if(key == sf::Keyboard::Key::H)
        return sf::String("H");
    else if(key == sf::Keyboard::Key::I)
        return sf::String("I");
    else if(key == sf::Keyboard::Key::J)
        return sf::String("J");
    else if(key == sf::Keyboard::Key::K)
        return sf::String("K");
    else if(key == sf::Keyboard::Key::L)
        return sf::String("L");
    else if(key == sf::Keyboard::Key::M)
        return sf::String("M");
    else if(key == sf::Keyboard::Key::N)
        return sf::String("N");
    else if(key == sf::Keyboard::Key::O)
        return sf::String("O");
    else if(key == sf::Keyboard::Key::P)
        return sf::String("P");
    else if(key == sf::Keyboard::Key::Q)
        return sf::String("Q");
    else if(key == sf::Keyboard::Key::R)
        return sf::String("R");
    else if(key == sf::Keyboard::Key::S)
        return sf::String("S");
    else if(key == sf::Keyboard::Key::T)
        return sf::String("T");
    else if(key == sf::Keyboard::Key::U)
        return sf::String("U");
    else if(key == sf::Keyboard::Key::V)
        return sf::String("V");
    else if(key == sf::Keyboard::Key::W)
        return sf::String("W");
    else if(key == sf::Keyboard::Key::X)
        return sf::String("X");
    else if(key == sf::Keyboard::Key::Y)
        return sf::String("Y");
    else if(key == sf::Keyboard::Key::Z)
        return sf::String("Z");
    else if(key == sf::Keyboard::Key::Escape)
        return sf::String("Escape");
    else if(key == sf::Keyboard::Key::Tab)
        return sf::String("Tab");
    else if(key == sf::Keyboard::Key::Left)
        return sf::String("Left Arrow");
    else if(key == sf::Keyboard::Key::Right)
        return sf::String("Right Arrow");
    else if(key == sf::Keyboard::Key::Up)
        return sf::String("Up Arrow");
    else if(key == sf::Keyboard::Key::Down)
        return sf::String("Down Arrow");
    else if(key == sf::Keyboard::Key::Enter)
        return sf::String("Enter");

    return sf::String("Error");
}

sf::Keyboard::Key toKey(const sf::String &key)
{
    if(key == "A")
       return sf::Keyboard::Key::A;
    else if(key == "B")
       return sf::Keyboard::Key::B;
    else if(key == "C")
       return sf::Keyboard::Key::C;
    else if(key == "D")
       return sf::Keyboard::Key::D;
    else if(key == "E")
       return sf::Keyboard::Key::E;
    else if(key == "F")
       return sf::Keyboard::Key::F;
    else if(key == "G")
       return sf::Keyboard::Key::G;
    else if(key == "H")
       return sf::Keyboard::Key::H;
    else if(key == "I")
       return sf::Keyboard::Key::I;
    else if(key == "J")
       return sf::Keyboard::Key::J;
    else if(key == "K")
       return sf::Keyboard::Key::K;
    else if(key == "L")
       return sf::Keyboard::Key::L;
    else if(key == "M")
       return sf::Keyboard::Key::M;
    else if(key == "N")
       return sf::Keyboard::Key::N;
    else if(key == "O")
       return sf::Keyboard::Key::O;
    else if(key == "P")
       return sf::Keyboard::Key::P;
    else if(key == "Q")
       return sf::Keyboard::Key::Q;
    else if(key == "R")
       return sf::Keyboard::Key::R;
    else if(key == "S")
       return sf::Keyboard::Key::S;
    else if(key == "T")
       return sf::Keyboard::Key::T;
    else if(key == "U")
       return sf::Keyboard::Key::U;
    else if(key == "V")
       return sf::Keyboard::Key::V;
    else if(key == "W")
       return sf::Keyboard::Key::W;
    else if(key == "X")
       return sf::Keyboard::Key::X;
    else if(key == "Y")
       return sf::Keyboard::Key::Y;
    else if(key == "Z")
       return sf::Keyboard::Key::Z;
    else if(key == "Escape")
       return sf::Keyboard::Key::Escape;
    else if(key == "Tab")
       return sf::Keyboard::Key::Tab;
    else if(key == "Left Arrow")
       return sf::Keyboard::Key::Left;
    else if(key == "Right Arrow")
       return sf::Keyboard::Key::Right;
    else if(key == "Up Arrow")
       return sf::Keyboard::Key::Up;
    else if(key == "Down Arrow")
       return sf::Keyboard::Key::Down;
    else if(key == "Enter")
       return sf::Keyboard::Key::Enter;


    return sf::Keyboard::Key::Unknown;
}
