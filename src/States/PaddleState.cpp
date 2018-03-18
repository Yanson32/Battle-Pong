#include "States/PaddleState.h"
#include <GameUtilities/Engin/Engin.h>
#include "Objects/Paddle.h"
#include "Objects/Wall.h"
#include "Objects/Ball.h"
#include "States/ControlState.h"
#include "States/Id.h"
#include "Events/Events.h"
#include "Settings.h"
#include "ResourceManager.h"
PaddleState::PaddleState(GU::Engin::Engin& newEngin, std::shared_ptr<PaddleSettings> pSettings):
StateBase(newEngin, stateId::PADDLE_STATE),
paddleSettings(pSettings)
{
    //ctor
//    gui.add(pSettings);

    const float labelX = 200;
    const float x = 300;
    nameLable = tgui::Label::create("Name");
    nameLable->setPosition({labelX, 50});
    gui.add(nameLable);

    eBox = tgui::EditBox::create();
    eBox->connect("ReturnKeyPressed", &PaddleState::onNameBox, this);
    eBox->setDefaultText(pSettings->getPlayerName());
    eBox->setPosition({x, 50});


    inputLable = tgui::Label::create("AI");
    inputLable->setPosition({labelX, 100});


    cBox = tgui::ComboBox::create();
    cBox->connect("ItemSelected", &PaddleState::onListItemSelected, this);
    cBox->setPosition({x, 100});
    cBox->addItem("Hard");
    cBox->addItem("Medium");
    cBox->addItem("Easy");
    cBox->addItem("None");
    cBox->setSelectedItem(paddleSettings->getInputType());


    backButton = tgui::Button::create("Back");
    backButton->setSize(Settings::inst().buttonSize());
    backButton->setPosition(Settings::inst().buttonPosition(4));
    backButton->connect("pressed", &PaddleState::onBack, this);

}


void PaddleState::HandleEvents(GU::Engin::Engin& newEngin, const int &deltaTime)
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
        StateBase::guEvent(engin, evtPtr);
        guEvent(engin, evtPtr);
    }
}

void PaddleState::Update(GU::Engin::Engin& engin, const int &deltaTime)
{
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

void PaddleState::Draw(GU::Engin::Engin& engin, const int &deltaTime)
{
    StateBase::Draw(engin, deltaTime);
    window.draw(*ball);
    window.display();
}

void PaddleState::onBack()
{
    engin.Pop();
    EventManager::inst().Post<GU::Evt::PlaySound>("Button Sound");
}

void PaddleState::onNameBox()
{
    paddleSettings->setPlayerName(eBox->getText());

    switch(paddleSettings->getId())
    {
        case ObjectId::LEFT_PADDLE:
            paddle1Hud->setName(eBox->getText());
        break;

        case ObjectId::RIGHT_PADDLE:
            paddle2Hud->setName(eBox->getText());
        break;
    }
}

void PaddleState::onListItemSelected()
{
    paddleSettings->setInputType(cBox->getSelectedItem());

}

void PaddleState::Init()
{
    StateBase::Init();
    ResourceManager::sound.load("Button Sound", "../Resources/Sounds/tone1.ogg");
    ResourceManager::sound.load("Ball Sound", "../Resources/Sounds/tone1.ogg");
    gui.add(eBox);
    gui.add(inputLable);
    gui.add(cBox);
    gui.add(backButton);
}

void PaddleState::Clean()
{
    gui.removeAllWidgets();
    ResourceManager::sound.remove("Button Sound");
    ResourceManager::sound.remove("Ball Sound");
}

void PaddleState::sfEvent(GU::Engin::Engin& engin, const sf::Event &event)
{

}

void PaddleState::guEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event)
{

}

PaddleState::~PaddleState()
{
    //dtor
}
