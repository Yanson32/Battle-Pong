#include "States/ConnectState.h"
#include <GameUtilities/Engin/Engin.h>
#include "Objects/Paddle.h"
#include "Objects/Ball.h"
#include "ResourceManager.h"
#include "States/ClientPlayState.h"
#include "SFMLFunctions.h"
#include "Events/Events.h"
#include "Sounds/Id.h"

ConnectState::ConnectState(GU::Engin::Engin& engin): StateBase(engin, stateId::CONNECT_STATE)
{
    //ctor
    backButton = tgui::Button::create("Back");
    backButton->connect("pressed", &ConnectState::onBackPressed, this);
    backButton->setPosition(Settings::inst().buttonPosition(4));
    backButton->setSize(Settings::inst().buttonSize());

    //Ip address label
    ipLabel = tgui::Label::create("Ip Lable");
    ipLabel->setText("Ip address");
    ipLabel->setPosition({200, 200});

    //EditBox to enter ip address
    ipBox = tgui::EditBox::create();
    ipBox->setPosition({350, 200});

    //Port number lable
    portLabel = tgui::Label::create("Port Lable");
    portLabel->setText("Port Number");
    portLabel->setPosition({200, 250});

    //EditBox to enter port number
    portBox = tgui::EditBox::create();
    portBox->setPosition({350, 250});

    connectButton = tgui::Button::create("Connect");
    connectButton->connect("pressed", &ConnectState::onConnectPressed, this);
    connectButton->setPosition({200, 300});

    portBox->setInputValidator("[0-9]+");

    sf::String port("5000");
    portBox->setDefaultText(port);
    portBox->setText(port);

    sf::String ip("127.0.0.1");
    ipBox->setText(ip);
    ipBox->setText(ip);
    ipBox->setInputValidator("[0-9.]+");


}

void ConnectState::HandleEvents(GU::Engin::Engin& engin, const float &deltaTime)
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

void ConnectState::Update(GU::Engin::Engin& engin, const float &deltaTime)
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

void ConnectState::Draw(GU::Engin::Engin& engin, const float &deltaTime)
{
	window.draw(*ball);
	StateBase::Draw(engin, deltaTime);
	//window.draw(header);
    window.display();
}

void ConnectState::Init()
{
    StateBase::Init();
//    panel->setSize({400, 300});
//    panel->setPosition({200, 200});

    gui.add(ipLabel);
    gui.add(ipBox);
    gui.add(portLabel);
    gui.add(portBox);
    gui.add(connectButton);

    //gui.add(panel);
    gui.add(backButton);
    ResourceManager::sound.load(Sound::Id::BUTTON, "../Resources/Sounds/tone1.ogg");
    ResourceManager::sound.load(Sound::Id::BALL, "../Resources/Sounds/tone1.ogg");
}

void ConnectState::Clean()
{
    ResourceManager::sound.remove(Sound::Id::BUTTON);
    ResourceManager::sound.remove(Sound::Id::BALL);

    gui.removeAllWidgets();
}

void ConnectState::onBackPressed()
{
    EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
    EventManager::inst().Post<GU::Evt::Pop>();
}

void ConnectState::onConnectPressed()
{
    EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
    int port = toInt(portBox->getText());
    sf::String ip = ipBox->getText();

    Settings::inst().clientSettings->setIp(ip);
    Settings::inst().clientSettings->setPort(port);

    EventManager::inst().Post<GU::Evt::ChangeState>(stateId::CONNECT_STATE);
}

void ConnectState::sfEvent(GU::Engin::Engin& engin, const sf::Event &event)
{

}

void ConnectState::handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event)
{
        StateBase::handleGUEvent(engin, event);

        //GameUtilities event loop
//        while(EventManager::inst().Poll((event)))
//        {
//            //EventManager::inst().Dispatch((evtPtr));
//            switch(event->id)
//            {
//
//                case EventId::CHANGE_STATE:
//                {
//                    std::shared_ptr<GU::Evt::ChangeState> temp =  std::dynamic_pointer_cast<GU::Evt::ChangeState>(event);
//                    switch(temp->id)
//                    {
//                        case stateId::CONNECT_STATE:
//                            std::cout << "Connect state" << std::endl;
//                        break;
//
//                    }
//                }
//                break;
//
//            }
//
//        }
}

ConnectState::~ConnectState()
{
    //dtor
}
