#include "Gui/PaddleHud.h"
#include <sstream>
#include <SFML/Network.hpp>
#include "Settings.h"

namespace Gui
{

    PaddleHud::PaddleHud(std::string &name, int &score):
    m_name(name), m_score(score)
    {
        //ctor
        panleLable = tgui::Label::create(name);
        panleLable->setText(name);
        this->add(panleLable);

        setScore(score);

        this->setSize({150, Settings::wallThickness});


        scoreLabel = tgui::Label::create();
        scoreLabel->setPosition({100, 0});
        scoreLabel->setText("0");
        scoreLabel->getRenderer()->setTextColor(sf::Color::Black);
        this->add(scoreLabel);

        this->getRenderer()->setBackgroundColor(sf::Color::Transparent);

    }

    void PaddleHud::setScore(const sf::Uint32 &score, const std::string &name)
    {
        std::stringstream ss;
        ss << name;
        ss << " ";
        ss << score;

        sf::String temp(ss.str());

        if(scoreLabel)
            scoreLabel->setText(temp.toAnsiString());

        m_score = score;
    }

    sf::Uint32 PaddleHud::getScore() const
    {
        return m_score;
    }

    void PaddleHud::setName(const sf::String &name)
    {
        panleLable->setText(name.toAnsiString());
    }
    sf::Packet& operator <<(sf::Packet& packet, const std::shared_ptr<Gui::PaddleHud> m)
    {
        packet << m->getScore();
        return packet;
    }
     
    sf::Packet& operator >>(sf::Packet& packet, std::shared_ptr<Gui::PaddleHud> m)
    {
        sf::Uint32 score;
        packet >> score;
        m->setScore(score);
        return packet;
    }

    PaddleHud::~PaddleHud()
    {
        //dtor
    }
}
