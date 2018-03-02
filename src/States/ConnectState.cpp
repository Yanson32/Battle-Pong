#include "States/ConnectState.h"
#include <GameUtilities/Engin/Engin.h>
#include "Objects/Paddle.h"
#include "Objects/Ball.h"
#include "ResourceManager.h"
#include "Events/EventManager.h"
#include "Events/PlaySound.h"
#include "States/ClientPlayState.h"
#include "SFMLFunctions.h"


ConnectState::ConnectState(Engin::Engin& engin): StateBase(engin, stateId::CONNECT_STATE)
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

void ConnectState::HandleEvents(Engin::Engin& engin, const int &deltaTime)
{
    if(window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {

            gui.handleEvent(event);
            switch (event.type)
            {

                case sf::Event::Closed:
					engin.Quit();
                    break;


                case sf::Event::KeyPressed:
                    break;

                default:
                    break;
            }
        }
        leftPaddle->handleInput(*ball);
        rightPaddle->handleInput(*ball);


    }

    gameEvents();
}

void ConnectState::Update(Engin::Engin& engin, const int &deltaTime)
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

void ConnectState::Draw(Engin::Engin& engin, const int &deltaTime)
{
	StateBase::Draw(engin, deltaTime);
	//window.draw(header);
	window.draw(*ball);
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
    ResourceManager::sound.load("Button Sound", "../Resources/Sounds/tone1.ogg");
    ResourceManager::sound.load("Ball Sound", "../Resources/Sounds/tone1.ogg");
}

void ConnectState::Clean()
{
    ResourceManager::sound.remove("Button Sound");
    ResourceManager::sound.remove("Ball Sound");

    gui.removeAllWidgets();
}

void ConnectState::onBackPressed()
{
    EventManager::inst().Post<PlaySound>("Button Sound");
    engin.Pop();
}

void ConnectState::onConnectPressed()
{
    EventManager::inst().Post<PlaySound>("Button Sound");
    sf::String value = portBox->getText();
    sf::String ip = ipBox->getText();
    std::unique_ptr<Client> client(new Client(ip, toInt(value)));
    engin.Push<ClientPlayState>(engin, std::move(client));
}

ConnectState::~ConnectState()
{
    //dtor
}
