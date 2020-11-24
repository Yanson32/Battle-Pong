#include "PaddleHud.h"
#include <sstream>
PaddleHud::PaddleHud(tempSettings::PaddleSettings &newPaddleSettings): paddleSettings(newPaddleSettings)
{
    //ctor
    panleLable = tgui::Label::create(paddleSettings.name);
    panleLable->setText(paddleSettings.name);
    this->add(panleLable);

    setScore(paddleSettings.score);

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
        scoreLabel->setText(temp);

    paddleSettings.score = newScore;
}

void PaddleHud::setName(const sf::String &name)
{
    panleLable->setText(name);
}

PaddleHud::~PaddleHud()
{
    //dtor
}
