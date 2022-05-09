#include "Gui/OptionsPanel/IntroPanel.h"
#include <iostream>
#include "Events/EventManager.h"
#include "GameUtilities/Event/PlaySound.h"
#include "States/StateId.h"
#include <GameUtilities/Event/PushState.h>
#include <GameUtilities/Event/Click.h>
#include "Gui/ButtonId.h"
IntroPanel::IntroPanel()
{
    //Create start button
    start = tgui::Button::create();
    start->setText("Start");
    start->onPress([](){
        EventManager::inst().Post<GU::Evt::Click>(Button::id::START);
    });

    tgui::HorizontalLayout::Ptr startLayout = tgui::HorizontalLayout::create();
    startLayout->addSpace(1);
    startLayout->add(start);
    startLayout->addSpace(1);
    getContentPane()->append(startLayout);

    getContentPane()->appendSpace();

    //Create MultiPlayer button
    multiPlayer = tgui::Button::create();
    multiPlayer->setText("Multiplayer");
    multiPlayer->onPress([](){
        EventManager::inst().Post<GU::Evt::Click>(Button::id::MULTIPLAYER);
    });

    tgui::HorizontalLayout::Ptr multiplayerLayout = tgui::HorizontalLayout::create();
    multiplayerLayout->addSpace(1);
    multiplayerLayout->add(multiPlayer);
    multiplayerLayout->addSpace(1);
    getContentPane()->append(multiplayerLayout);

    getContentPane()->appendSpace();

    //Create Options button
    options = tgui::Button::create();
    options->setText("Options");
    options->onPress([](){
        EventManager::inst().Post<GU::Evt::Click>(Button::id::OPTIONS);
    });
    tgui::HorizontalLayout::Ptr optionLayout = tgui::HorizontalLayout::create();
    optionLayout->addSpace(1);
    optionLayout->add(options);
    optionLayout->addSpace(1);
    getContentPane()->append(optionLayout);

    getContentPane()->appendSpace();
    
    //Create credits button
    credits = tgui::Button::create();
    credits->setText("Credits");
    credits->onPress([](){
        EventManager::inst().Post<GU::Evt::Click>(Button::id::CREDITS);
    });

    tgui::HorizontalLayout::Ptr creditsLayout = tgui::HorizontalLayout::create();
    creditsLayout->addSpace(1);
    creditsLayout->add(credits);
    creditsLayout->addSpace(1);
    getContentPane()->append(creditsLayout);
}

void IntroPanel::init(const int &width, const int &height)
{
    this->setSize(width / 2, height / 2);
    this->setPosition(width / 4, height / 4);
}

IntroPanel::~IntroPanel()
{
    //dtor
}
