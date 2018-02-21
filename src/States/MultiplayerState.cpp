#include "States/MultiplayerControlsState.h"
#include "GameUtilities/Engin/Engin.h"
#include <GameUtilities/Event/Event.h>
#include <GameUtilities/Event/EventQueue.h>

#include "Settings.h"

#include "Objects/Wall.h"
#include "Objects/Ball.h"
#include "Objects/Paddle.h"

#include "Events/EventManager.h"
#include "Events/PlaySound.h"
#include "ResourceManager.h"


std::shared_ptr<MultiplayerPanel> MultiplayerState::panel(new MultiplayerPanel());

MultiplayerPanel::MultiplayerPanel()
{
    //Ip address label
    ipLabel = tgui::Label::create("Ip Lable");
    ipLabel->setText("Ip address");
    this->add(ipLabel);

    //EditBox to enter ip address
    ipBox = tgui::EditBox::create();
    ipBox->setPosition({150, 0});
    this->add(ipBox);

    //Port number lable
    portLabel = tgui::Label::create("Port Lable");
    portLabel->setText("Port Number");
    portLabel->setPosition({0, 50});
    this->add(portLabel);

    //EditBox to enter port number
    portBox = tgui::EditBox::create();
    portBox->setPosition({150, 50});
    this->add(portBox);


    hostButton = tgui::Button::create("Host");
    hostButton->connect("pressed", &MultiplayerPanel::onHostPressed, this);
    hostButton->setPosition({0, 100});
    this->add(hostButton);

    setBackgroundColor(sf::Color::Transparent);
}

void MultiplayerPanel::Init()
{

}

void MultiplayerPanel::onHostPressed()
{

}
MultiplayerState::MultiplayerState(Engin::Engin& engin): StateBase(engin)
{
    //ctor
    backButton = tgui::Button::create("Back");
    backButton->connect("pressed", &MultiplayerState::onBackPressed, this);
    backButton->setPosition(Settings::inst().buttonPosition(4));
    backButton->setSize(Settings::inst().buttonSize());


}

void MultiplayerState::Init()
{
    StateBase::Init();
    ResourceManager::sound.load("Button Sound", "../Resources/Sounds/tone1.ogg");
    ResourceManager::sound.load("Ball Sound", "../Resources/Sounds/tone1.ogg");
    gui.add(backButton);

    panel->setSize({400, 300});
    panel->setPosition({100, 100});

    gui.add(panel);
}
void MultiplayerState::Clean()
{
    ResourceManager::sound.remove("Button Sound");
    ResourceManager::sound.remove("Ball Sound");
    gui.removeAllWidgets();
}
/****************************************************************//**
*   @brief  This method handles input such as user input and events.
*           This should be called once per frame.
*   @param  engin A reference to an Engin::Engin object.
*           This is the main game object.
********************************************************************/
void MultiplayerState::HandleEvents(Engin::Engin& newEngin, const int &deltaTime)
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

/****************************************************************//**
*   @brief  This method updates the game logic. This should be
*           called once per frame.
*   @param  engin A reference to an Engin::Engin object.
*           This is the main game object.
********************************************************************/
void MultiplayerState::Update(Engin::Engin& engin, const int &deltaTime)
{
    StateBase::Update(engin, deltaTime);
    world->Step( timeStep, velocityIterations, positionIterations);
    debugDraw.update();
    ball->update();
    ground->update();
    celing->update();
    leftWall->update();
    RightWall->update();
    leftPaddle->update();
    rightPaddle->update();
}


/****************************************************************//**
*   @brief  This method draws the current frame. This should be
*           called once per frame.
*   @param  engin A reference to an Engin::Engin object.
*           This is the main game object.
********************************************************************/
void MultiplayerState::Draw(Engin::Engin& engin, const int &deltaTime)
{
	StateBase::Draw(engin, deltaTime);
	window.draw(*ball);
	window.draw(*backButton);
    window.display();
}

void MultiplayerState::onBackPressed()
{
    std::cout << "onBackPressed" << std::endl;
    engin.Pop();
    EventManager::inst().Post<PlaySound>("Button Sound");
}

MultiplayerState::~MultiplayerState()
{
    //dtor
}
