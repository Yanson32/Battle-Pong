#include "Settings.h"
#include "Events/Events.h"
#include "States/Id.h"
#include <iostream>
/**********************************************************//**
*   @brief  Settings for the game window
**************************************************************/
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


/**********************************************************//**
*   @brief  Settings for a single paddle
**************************************************************/
PaddleSettings::PaddleSettings(const sf::String &newName, ObjectId newId):
tgui::Panel(),
playerName(newName),
paddleId(newId)
{
//    this->setSize({400, 130});
//    this->setPosition({225, 100});
//    this->setBackgroundColor(sf::Color::Transparent);
//
//
//    auto panleLable = tgui::Label::create(name);
//    this->add(panleLable);
//
//    auto nameLable = tgui::Label::create("Name");
//    nameLable->setPosition({0, 50});
//    this->add(nameLable);
//
//    eBox = tgui::EditBox::create();
//    eBox->connect("ReturnKeyPressed", &PaddleSettings::onNameBox, this);
//    eBox->setDefaultText(playerName);
//    eBox->setPosition({100, 50});
//    this->add(eBox);
//
//    auto inputLable = tgui::Label::create("AI");
//    inputLable->setPosition({0, 100});
//    this->add(inputLable);
//
//    cBox = tgui::ComboBox::create();
//    cBox->connect("ItemSelected", &PaddleSettings::onListItemSelected, this);
//    cBox->setPosition({100, 100});
//    cBox->addItem("Hard");
//    cBox->addItem("Medium");
//    cBox->addItem("Easy");
//    cBox->addItem("None");
//    cBox->setSelectedItem("Medium");
//    this->add(cBox);
    input = "Medium";
}

//void PaddleSettings::onNameBox()
//{
//
//    playerName = eBox->getText();
//    EventManager::inst().Post<PlaySound>("Edit Box Sound");
//}
//
//void PaddleSettings::onListItemSelected()
//{
//    cBoxItem = cBox->getSelectedItem();
//    EventManager::inst().Post<PlaySound>("List Box Selected Sound");
//}

sf::String PaddleSettings::getPlayerName() const
{
    return playerName;
}

sf::String PaddleSettings::getInputType() const
{
    return input;
}

int PaddleSettings::getScore() const
{
    return score;
}

void PaddleSettings::setScore(const int newScore)
{
    score = newScore;
}

void PaddleSettings::setPlayerName(const sf::String &newName)
{
    playerName = newName;
}



void PaddleSettings::setInputType(const sf::String &newInput)
{
    input = newInput;
}

ObjectId PaddleSettings::getId() const
{
    return paddleId;
}

PaddleSettings::~PaddleSettings()
{

}


/**********************************************************//**
*   @brief  The MusicSettings constructor
*************************************************************/
MusicSettings::MusicSettings(): tgui::Panel()
{
    this->setPosition({200, 300});
    this->setSize({450, 100});
    this->getRenderer()->setBackgroundColor(sf::Color::Transparent);

    auto musicLabel = tgui::Label::create("Music Volume");
    this->add(musicLabel);

    musicVolume = tgui::Slider::create();
    musicVolume->connect("ValueChanged", &MusicSettings::onMusicVolume, this);
    musicVolume->setPosition({200, 0});
    musicVolume->setValue(getVolume());
    musicVolume->setMaximum(255);
    this->add(musicVolume);

    auto soundLabel = tgui::Label::create("Sound Volume");
    soundLabel->setPosition(0, 50);
    this->add(soundLabel);

    soundVolume = tgui::Slider::create();
    soundVolume->connect("ValueChanged", &MusicSettings::onSoundVolume, this);
    soundVolume->setPosition({200, 50});
    soundVolume->setValue(getSoundVolume());
    soundVolume->setMaximum(255);
    this->add(soundVolume);
}

int MusicSettings::getVolume() const
{
    return mVolume;
}

int MusicSettings::getSoundVolume() const
{
    return sVolume;
}

void MusicSettings::onMusicVolume()
{
    mVolume = musicVolume->getValue();
    EventManager::inst().Post<GU::Evt::MusicVolumeChanged>();
}


void MusicSettings::onSoundVolume()
{
    sVolume = soundVolume->getValue();
    EventManager::inst().Post<GU::Evt::SoundVolumeChanged>();
}


ServerSettings::ServerSettings()
{
    //ctor
    listener.setBlocking(true);
}

void ServerSettings::init()
{

    if (listener.listen(port) != sf::Socket::Done)
    {
        std::cerr << "unable to listen on port " << listener.getLocalPort() << std::endl;
        return;
    }


    if (listener.accept(socket) != sf::Socket::Done)
    {
        std::cerr << "unable to accept a connection on port " << listener.getLocalPort() << std::endl;
        return;
    }
}

void ServerSettings::clean()
{

}

void ServerSettings::handleEvents()
{

}


bool ServerSettings::update()
{



    return true;
}

bool ServerSettings::isConnected()
{
    return connected;
}


sf::Packet ServerSettings::recieve()
{

}

ServerSettings::~ServerSettings()
{
    //dtor
}

ClientSettings::ClientSettings()
{
    //ctor
    setTimeOut(sf::seconds(5));
}

bool ClientSettings::isConnected()
{

}

void ClientSettings::init()
{

    sf::Socket::Status status = socket.connect({ip}, port, sf::seconds(5));
    if (status != sf::Socket::Done)
    {
        // error...
        EventManager::inst().Post<GU::Evt::ChangeState>(stateId::CONNECT_STATE);
    }

}

void ClientSettings::clean()
{

}

void ClientSettings::handleEvents()
{

}

bool ClientSettings::update()
{

}

void ClientSettings::setTimeOut(const sf::Time &newTime)
{
    timeOut = newTime;
}


void ClientSettings::setIp(const sf::String newIp)
{
    ip = newIp;
}

void ClientSettings::setPort(const int newPort)
{
    port = newPort;
}

sf::String ClientSettings::getIp() const
{
    return ip;
}

int ClientSettings::getPort() const
{
    return port;
}

ClientSettings::~ClientSettings()
{
    //dtor
}


/**********************************************************//**
*   @brief  A singleton that contains all game settings
**************************************************************/
Settings::Settings():
bSize(200, 25),
bPosition(300, 300),
paddle1(new PaddleSettings("Paddle 1", ObjectId::LEFT_PADDLE)),
paddle2(new PaddleSettings("Paddle 2", ObjectId::RIGHT_PADDLE)),
clientSettings(new ClientSettings()),
serverSettings(new ServerSettings()),
musicSettings(new MusicSettings()),
screen(800, 600)
{
	title = "Pong";
	paddle1->setInputType(sf::String("None"));
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

