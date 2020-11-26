#include "States/HostState.h"
#include <GameUtilities/Engin/Engin.h>
#include "Objects/Paddle.h"
#include "Objects/Ball.h"
#include "ResourceManager.h"
#include "Events/Events.h"
#include "SFMLFunctions.h"
#include <SFML/Network.hpp>
#include <SFML/Network/IpAddress.hpp>
#include "Server.h"
#include "States/HostPlayState.h"
#include "Sounds/Id.h"

//std::shared_ptr<HostPanel> HostState::panel(new HostPanel());
//
//HostPanel::HostPanel()
//{
////    //Port number lable
////    portLabel = tgui::Label::create("Port");
////    portLabel->setPosition({0, 0});
////    this->add(portLabel);
////
////    //EditBox to enter port number
////    portBox = tgui::EditBox::create();
////    portBox->setPosition({150, 0});
////    this->add(portBox);
////
////    hostButton = tgui::Button::create("Host");
////    hostButton->connect("pressed", &HostPanel::onBackPressed, this);
////    hostButton->setPosition({0, 50});
////    this->add(hostButton);
////
////    setBackgroundColor(sf::Color::Transparent);
//}

//void HostPanel::Init()
//{
////    setSize({400, 300});
////    setPosition({200, 200});
//}
//
//void HostPanel::onBackPressed()
//{
//
//}
//
//void HostPanel::Clean()
//{
//
//}

HostState::HostState(GU::Engin::Engin& engin): StateBase(engin, stateId::HOST_STATE)
{
    //ctor
    backButton = tgui::Button::create("Back");
    backButton->connect("pressed", &HostState::onBackPressed, this);
    backButton->setPosition(tempSettings::button.bPosition);
    backButton->setSize(tempSettings::button.bSize);

    //Global Ip address label
    globalIpLabel = tgui::Label::create("Global Ip");
    globalIpLabel->setPosition({200, 200});

    sf::IpAddress address = sf::IpAddress::getPublicAddress();
    sf::String globalIp = address.toString();

    //EditBox to enter ip address
    globalIpBox = tgui::Label::create(globalIp);
    globalIpBox->setPosition({350, 200});

    //Global Ip address label
    localIpLabel = tgui::Label::create("Local Ip");
    localIpLabel->setPosition({200, 250});

    sf::IpAddress address2 = sf::IpAddress::getLocalAddress();
    sf::String localIp = address2.toString();

    //EditBox to enter ip address
    localIpBox = tgui::Label::create(localIp);
    localIpBox->setPosition({350, 250});

    //Port number lable
    portLabel = tgui::Label::create("Port");
    portLabel->setPosition({200, 300});


    //EditBox to enter port number
    portBox = tgui::EditBox::create();
    portBox->setPosition({350, 300});


    hostButton = tgui::Button::create("Host");
    hostButton->connect("pressed", &HostState::onHostPressed, this);
    hostButton->setPosition({200, 350});

    //portBox->setInputValidator("[0-9]+");

    sf::String port("5000");
    portBox->setDefaultText(port);
    portBox->setText(port);


    //globalIpBox->setInputValidator("[0-9.]+");
}

void HostState::HandleEvents(GU::Engin::Engin& engin, const float &deltaTime)
{
    if(window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            StateBase::sfEvent(engin, event);
            sfEvent(engin, event);
            gui.handleEvent(event);
        }
        leftPaddle->handleInput(*ball);
        rightPaddle->handleInput(*ball);
    }

    //GameUtilities event loop
    GU::Evt::EventPtr evtPtr;
    while(EventManager::inst().Poll((evtPtr)))
    {
        handleGUEvent(engin, evtPtr);
    }
}

void HostState::Update(GU::Engin::Engin& engin, const float &deltaTime)
{
    StateBase::Update(engin, deltaTime);
    world->Step( timeStep, velocityIterations, positionIterations);
    debugDraw.update();
    ball->update();
    //ground->update();
    //celing->update();
    //leftWall->update();
    //RightWall->update();
    leftPaddle->update();
    rightPaddle->update();
}

void HostState::Draw(GU::Engin::Engin& engin, const float &deltaTime)
{
	StateBase::Draw(engin, deltaTime);
	//window.draw(header);
	window.draw(*ball);
    window.display();
}

void HostState::Init()
{
    StateBase::Init();
    //panel->Init();
//
//    ResourceManager::sound.load(Sound::Id::BUTTON, "../Resources/Sounds/tone1.ogg");
//    ResourceManager::sound.load(Sound::Id::BALL, "../Resources/Sounds/tone1.ogg");
    gui.add(hostButton);
    gui.add(portBox);
    gui.add(portLabel);
    //gui.add(panel);
    gui.add(backButton);
    gui.add(globalIpLabel);
    gui.add(globalIpBox);
    gui.add(localIpLabel);
    gui.add(localIpBox);

}

void HostState::Clean()
{
    //panel->Clean();
//    ResourceManager::sound.remove(Sound::Id::BUTTON);
//    ResourceManager::sound.remove(Sound::Id::BALL);

    gui.removeAllWidgets();
}

void HostState::onBackPressed()
{
    EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
    EventManager::inst().Post<GU::Evt::Pop>();
}

void HostState::onHostPressed()
{
    EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
    EventManager::inst().Post<GU::Evt::ChangeState>(stateId::HOST_PLAY_STATE);

}


void HostState::sfEvent(GU::Engin::Engin& engin, const sf::Event &event)
{

}

void HostState::handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event)
{
    StateBase::handleGUEvent(engin, event);
}


HostState::~HostState()
{
    //dtor
}
