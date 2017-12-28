#include "PaddleHud.h"
#include <sstream>
PaddleHud::PaddleHud(std::shared_ptr<PaddleSettings> newPaddleSettings): paddleSettings(newPaddleSettings)
{
    //ctor
    panleLable = tgui::Label::create(paddleSettings->getPlayerName());
    panleLable->setText(paddleSettings->getPlayerName());
    this->add(panleLable);

    setScore(paddleSettings->getScore());

    this->setSize({150, 25});


    scoreLabel = tgui::Label::create();
    scoreLabel->setPosition({100, 0});
    scoreLabel->setText("0");
    this->add(scoreLabel);

    this->setBackgroundColor(sf::Color::Transparent);

}

void PaddleHud::setScore(const int newScore)
{
    std::stringstream ss;
    ss << newScore;

    sf::String temp(ss.str());

    if(scoreLabel)
        scoreLabel->setText(temp);

    if(paddleSettings)
        paddleSettings->setScore(newScore);
}

void PaddleHud::setName(const sf::String &name)
{
    panleLable->setText(name);
}

PaddleHud::~PaddleHud()
{
    //dtor
}
