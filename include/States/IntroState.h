#ifndef INTROSTATE_H
#define INTROSTATE_H


#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>

#include "States/StateBase.h"

class IntroState: public StateBase
{
    public:
        IntroState();
        virtual void HandleEvents(Engin::Engin& engin);
        virtual void Update(Engin::Engin& engin);
        virtual void Draw(Engin::Engin& engin);
        virtual ~IntroState();
    private:
        sf::Text header;
        sf::Color background = sf::Color::Black;
        sf::Font headerFont;
};

#endif // INTROSTATE_H
