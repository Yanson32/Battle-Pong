#include "Gui/IntroState/IntroGui.h"
#include <iostream>
#include "Events/EventManager.h"
#include "GameUtilities/Event/PlaySound.h"
#include "States/StateId.h"
#include <GameUtilities/Event/PushState.h>
#include <GameUtilities/Event/Click.h>
#include "Gui/ButtonId.h"
IntroGui::IntroGui()
{
    //Create start button
    start = tgui::Button::create();
    start->setText("Start");
    start->onPress([](){
        //EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
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
        //EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
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
        //EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
        EventManager::inst().Post<GU::Evt::Click>(Button::id::OPTIONS);
    });
    tgui::HorizontalLayout::Ptr optionLayout = tgui::HorizontalLayout::create(); 
    optionLayout->addSpace(1);
    optionLayout->add(options);
    optionLayout->addSpace(1);
    getContentPane()->append(optionLayout);
}

void IntroGui::init(const int &width, const int &height)
{
    this->setSize(width / 2, height / 2);
    this->setPosition(width / 4, height / 4);
}

IntroGui::~IntroGui()
{
    //dtor
}
