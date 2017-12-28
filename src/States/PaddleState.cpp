#include "States/PaddleState.h"
#include <GameUtilities/Engin/Engin.h>
#include "Objects/Paddle.h"
#include "Objects/Wall.h"
#include "Objects/Ball.h"
#include "States/ControlState.h"
#include "Events/EventManager.h"
#include "Events/PlaySound.h"
#include "Settings.h"
PaddleState::PaddleState(Engin::Engin& newEngin, std::shared_ptr<PaddleSettings> pSettings):
StateBase(newEngin),
paddleSettings(pSettings)
{
    //ctor
//    gui.add(pSettings);

    const float labelX = 200;
    const float x = 300;
    auto nameLable = tgui::Label::create("Name");
    nameLable->setPosition({labelX, 50});
    gui.add(nameLable);

    eBox = tgui::EditBox::create();
    eBox->connect("ReturnKeyPressed", &PaddleState::onNameBox, this);
    eBox->setDefaultText(pSettings->getPlayerName());
    eBox->setPosition({x, 50});
    gui.add(eBox);

    auto inputLable = tgui::Label::create("AI");
    inputLable->setPosition({labelX, 100});
    gui.add(inputLable);

    cBox = tgui::ComboBox::create();
    cBox->connect("ItemSelected", &PaddleState::onListItemSelected, this);
    cBox->setPosition({x, 100});
    cBox->addItem("Hard");
    cBox->addItem("Medium");
    cBox->addItem("Easy");
    cBox->addItem("None");
    cBox->setSelectedItem(paddleSettings->getInputType());
    gui.add(cBox);

    auto backButton = tgui::Button::create("Back");
    backButton->setSize(Settings::inst().buttonSize());
    backButton->setPosition(Settings::inst().buttonPosition(4));
    backButton->connect("pressed", &PaddleState::onBack, this);
    gui.add(backButton);

}


void PaddleState::HandleEvents(Engin::Engin& newEngin)
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
                    if(event.key.code == sf::Keyboard::P)
                    {
                        Pause(!IsPaused());
                    }
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

void PaddleState::Update(Engin::Engin& engin)
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

void PaddleState::Draw(Engin::Engin& engin)
{
    StateBase::Draw(engin);
    gui.draw();
    window.display();
}

void PaddleState::onBack()
{
    gui.removeAllWidgets();
    engin.ChangeState<ControlState>(engin);
    EventManager::inst().Post<PlaySound>("Button Sound");
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

PaddleState::~PaddleState()
{
    //dtor
}
