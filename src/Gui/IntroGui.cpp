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

    layout1->add(spacer);
    start = tgui::Button::create();
    start->setText("Start");
    start->connect("pressed", [](){
        EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
        EventManager::inst().Post<Click>(Button::id::START);
    });
    layout1->add(start);
    layout1->add(spacer);

    //Create MultiPlayer button
    layout3->add(spacer);
    multiPlayer = tgui::Button::create();
    multiPlayer->setText("Multiplayer");
    multiPlayer->connect("pressed", [](){
        EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
        EventManager::inst().Post<Click>(Button::id::MULTIPLAYER);
    });
    layout3->add(multiPlayer);
    layout3->add(spacer);

    //Create Options button
    layout5->add(spacer);
    options = tgui::Button::create();
    options->setText("Options");
    options->connect("pressed", [](){
        EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
        EventManager::inst().Post<Click>(Button::id::GENERAL_TAB);
    });
    layout5->add(options);
    layout5->add(spacer);
}

IntroGui::~IntroGui()
{
    //dtor
}
