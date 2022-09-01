#include "Gui/PaddleHud.h"
#include <sstream>


namespace GU
{
    namespace Gui
    {

        PaddleHud::PaddleHud(const std::string &input, std::string &name, int &score):
        m_input(input), m_name(name), m_score(score)
        {
            //ctor
            panleLable = tgui::Label::create(name);
            panleLable->setText(name);
            this->add(panleLable);

            setScore(score);

            this->setSize({150, 25});


            scoreLabel = tgui::Label::create();
            scoreLabel->setPosition({100, 0});
            scoreLabel->setText("0");
            this->add(scoreLabel);

            this->getRenderer()->setBackgroundColor(sf::Color::Transparent);

        }

        void PaddleHud::setScore(const int newScore)
        {
            std::stringstream ss;
            ss << newScore;

            sf::String temp(ss.str());

            if(scoreLabel)
                scoreLabel->setText(temp.toAnsiString());

            m_score = newScore;
        }

        void PaddleHud::setName(const sf::String &name)
        {
            panleLable->setText(name.toAnsiString());
        }

        PaddleHud::~PaddleHud()
        {
            //dtor
        }
    }
}
