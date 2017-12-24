#include "Settings.h"
#include <iostream>
#include "Events/PlaySound.h"
#include "Events/EventManager.h"

WindowSettings::WindowSettings(): vMode(800, 600)
{

}


sf::VideoMode WindowSettings::getVideoMode() const
{
    return vMode;
}


WindowSettings::~WindowSettings()
{

}


PaddleSettings::PaddleSettings(const sf::String &newName):
tgui::Panel(),
name(newName)
{
    this->setSize({400, 130});
    this->setPosition({200, 100});
    this->setBackgroundColor(sf::Color::Transparent);


    auto panleLable = tgui::Label::create(name);
    this->add(panleLable);

    auto nameLable = tgui::Label::create("Name");
    nameLable->setPosition({0, 50});
    this->add(nameLable);

    eBox = tgui::EditBox::create();
    eBox->connect("ReturnKeyPressed", &PaddleSettings::onNameBox, this);
    eBox->setDefaultText(playerName);
    eBox->setPosition({100, 50});
    this->add(eBox);

    auto inputLable = tgui::Label::create("AI");
    inputLable->setPosition({0, 100});
    this->add(inputLable);

    cBox = tgui::ComboBox::create();
    cBox->connect("ItemSelected", &PaddleSettings::onListItemSelected, this);
    cBox->setPosition({100, 100});
    cBox->addItem("Hard");
    cBox->addItem("Medium");
    cBox->addItem("Easy");
    cBox->addItem("None");
    cBox->setSelectedItem("Medium");
    this->add(cBox);
}

void PaddleSettings::onNameBox()
{

    playerName = eBox->getText();
    EventManager::inst().Post<PlaySound>("Edit Box Sound");
}

void PaddleSettings::onListItemSelected()
{
    cBoxItem = cBox->getSelectedItem();
    EventManager::inst().Post<PlaySound>("List Box Selected Sound");
}

sf::String PaddleSettings::getPlayerName() const
{
    return playerName;
}

sf::String PaddleSettings::getInputType() const
{
    return cBoxItem;
}

PaddleSettings::~PaddleSettings()
{

}


Settings::Settings():
bSize(200, 25),
bPosition(300, 300),
paddle1(new PaddleSettings("Paddle 1")),
paddle2(new PaddleSettings("Paddle 2"))
{
	title = "Pong";
}

sf::String Settings::getTitle() const
{
	return title;
}

Settings::~Settings()
{
}


Settings& Settings::inst()
{
	static Settings settings;
	return settings;
}

WindowSettings Settings::getWindowSettings() const
{
    return windowSettings;
}

sf::Vector2f Settings::buttonSize() const
{
    return bSize;
}

sf::Vector2f Settings::buttonPosition(const unsigned pos) const
{

    sf::Vector2f temp = bPosition;
    temp.y += 50 * pos;

    return temp;
}
