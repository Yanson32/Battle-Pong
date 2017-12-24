#ifndef PONG_PLAYSTATE_H
#define PONG_PLAYSTATE_H
#include "States/StateBase.h"
#include <memory>
#include "Ball.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Clock.hpp>


class PlayState: public StateBase
{
    public:
        PlayState(Engin::Engin& newEngin);
        void HandleEvents(Engin::Engin& newEngin);
        void Update(Engin::Engin& engin);
        void Draw(Engin::Engin& engin);
        ~PlayState();
    private:
        sf::Text userMessage;
        sf::Font font;
        sf::Clock messageClock;
};
#endif
