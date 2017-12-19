#ifndef INTROSTATE_H
#define INTROSTATE_H


#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>

#include "States/StateBase.h"
#include <GameUtilities/Engin/Engin.h>

class IntroState: public StateBase
{
    public:
        IntroState(Engin::Engin& engin);
        virtual void HandleEvents(Engin::Engin& engin);
        virtual void Update(Engin::Engin& engin);
        virtual void Draw(Engin::Engin& engin);
        void clean();
        virtual ~IntroState();
    private:
        void onStartPressed();
        sf::Text header;
        sf::Color background = sf::Color::Black;
        sf::Font headerFont;
        Engin::Engin& engin;
};

#endif // INTROSTATE_H
