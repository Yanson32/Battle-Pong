#include "States/HostState.h"
#include <GameUtilities/Engin/Engin.h>
#include "Objects/Paddle.h"
#include "Objects/Ball.h"
#include "ResourceManager.h"
#include "Events/Events.h"
#include "States/HostPlayState.h"
#include "Events/ChangeState.h"
#include "SFMLFunctions.h"
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

HostState::HostState(Engin::Engin& engin): StateBase(engin, stateId::HOST_STATE)
{
    //ctor
    backButton = tgui::Button::create("Back");
    backButton->connect("pressed", &HostState::onBackPressed, this);
    backButton->setPosition(Settings::inst().buttonPosition(4));
    backButton->setSize(Settings::inst().buttonSize());

    //Port number lable
    portLabel = tgui::Label::create("Port");
    portLabel->setPosition({200, 200});


    //EditBox to enter port number
    portBox = tgui::EditBox::create();
    portBox->setPosition({350, 200});


    hostButton = tgui::Button::create("Host");
    hostButton->connect("pressed", &HostState::onHostPressed, this);
    hostButton->setPosition({200, 250});

    portBox->setInputValidator("[0-9]+");

    sf::String port("5000");
    portBox->setDefaultText(port);
    portBox->setText(port);
}

void HostState::HandleEvents(Engin::Engin& engin, const int &deltaTime)
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

    //GameUtilities event loop
    Evt::EventPtr evtPtr;
    while(EventManager::inst().Poll((evtPtr)))
    {
        switch(evtPtr->id)
        {
            case EventId::LEFT_GOAL_COLLISION:
            {
                int currentScore = Settings::inst().paddle1->getScore();
                Settings::inst().paddle1->setScore(currentScore + 1);
                paddle1Hud->setScore(currentScore + 1);
                reset();
            }
            break;
            case EventId::RIGHT_GOAL_COLLISION:
            {
                int currentScore = Settings::inst().paddle2->getScore();
                Settings::inst().paddle2->setScore(currentScore + 1);
                paddle2Hud->setScore(currentScore + 1);
                reset();
            }
            break;
            case EventId::PLAY_SOUND:
            {
                std::shared_ptr<PlaySound> temp =  std::dynamic_pointer_cast<PlaySound>(evtPtr);

                if(temp && ResourceManager::sound.isLoaded(temp->soundId))
                {
                    sound.setBuffer(ResourceManager::sound.get(temp->soundId));
                    sound.play();
                }
            }
            break;
            case BALL_COLLISION:
                EventManager::inst().Post<PlaySound>("Ball Sound");
            break;
            case EventId::CHANGE_STATE:
            {
                std::shared_ptr<ChangeState> temp =  std::dynamic_pointer_cast<ChangeState>(evtPtr);
                switch(temp->state)
                {
                    case stateId::HOST_PLAY_STATE:
                            EventManager::inst().Post<PlaySound>("Button Sound");
                            sf::String value = portBox->getText();
                            std::unique_ptr<Server> serverPtr(new Server(toInt(value)));
                            engin.Push<HostPlayState>(engin, std::move(serverPtr));
                    break;
                }
            }
            break;
            case EventId::POP_STATE:
                EventManager::inst().Post<PlaySound>("Button Sound");
                engin.Pop();
            break;
        }

    }
}

void HostState::Update(Engin::Engin& engin, const int &deltaTime)
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

void HostState::Draw(Engin::Engin& engin, const int &deltaTime)
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

    ResourceManager::sound.load("Button Sound", "../Resources/Sounds/tone1.ogg");
    ResourceManager::sound.load("Ball Sound", "../Resources/Sounds/tone1.ogg");
    gui.add(hostButton);
    gui.add(portBox);
    gui.add(portLabel);
    //gui.add(panel);
    gui.add(backButton);



}

void HostState::Clean()
{
    //panel->Clean();
    ResourceManager::sound.remove("Button Sound");
    ResourceManager::sound.remove("Ball Sound");

    gui.removeAllWidgets();
}

void HostState::onBackPressed()
{
    EventManager::inst().Post<Pop>();
}

void HostState::onHostPressed()
{
    EventManager::inst().Post<ChangeState>(stateId::HOST_PLAY_STATE);
}



HostState::~HostState()
{
    //dtor
}
