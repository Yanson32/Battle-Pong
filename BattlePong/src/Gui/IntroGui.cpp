#include "Gui/IntroGui.h"
#include <iostream>
#include "Events/EventManager.h"
#include "GameUtilities/Event/PlaySound.h"
#include "States/Id.h"
#include "Sounds/Id.h"
#include <GameUtilities/Event/PushState.h>
#include "Events/Click.h"
#include "Gui/ButtonId.h"
IntroGui::IntroGui()
{
    //Create start button
    start = tgui::Button::create();
    start->setText("Start");
    start->connect("pressed", [](){
        EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
        EventManager::inst().Post<Click>(Button::id::START);
    });
    layout1->addSpace(1);
    layout1->add(start);
    layout1->addSpace(1);

    //Create MultiPlayer button
    multiPlayer = tgui::Button::create();
    multiPlayer->setText("Multiplayer");
    multiPlayer->connect("pressed", [](){
        EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
        EventManager::inst().Post<Click>(Button::id::MULTIPLAYER);
    });
    layout3->addSpace(1);
    layout3->add(multiPlayer);
    layout3->addSpace(1);

    //Create Options button
    options = tgui::Button::create();
    options->setText("Options");
    options->connect("pressed", [](){
        EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
        EventManager::inst().Post<Click>(Button::id::GENERAL_TAB);
    });
    layout5->addSpace(1);
    layout5->add(options);
    layout5->addSpace(1);
}

IntroGui::~IntroGui()
{
    //dtor
}
