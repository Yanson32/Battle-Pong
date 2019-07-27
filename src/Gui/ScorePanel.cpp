#include "Gui/ScorePanel.h"
#include <sstream>
#include <iostream>
namespace Gui
{
    ScorePanel::ScorePanel(const sf::String &newText):
    text(newText)
    {
        //ctor
        //this->add(paddle);
        //this->add(score);
        paddleLable = tgui::Label::create(text + " 0");
        paddleLable->getRenderer()->setTextColor(sf::Color::Black);
        paddleLable->setPosition("parent.width / 2 - width / 2", "0");
        this->add(paddleLable);
//        scoreLable = tgui::Label::create("0");
//        scoreLable->setPosition({200, 0});
//        scoreLable->getRenderer()->setTextColor(sf::Color::Black);
//        this->add(scoreLable);

        this->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    }

    void ScorePanel::setScore(const int newScore)
    {

        score = newScore;

        std::stringstream ss;
        ss << text;
        ss << " ";
        ss << newScore;
        paddleLable->setText(ss.str());
    }

    int ScorePanel::getScore() const
    {
        return score;
    }

    ScorePanel::~ScorePanel()
    {
        //dtor
    }
}
