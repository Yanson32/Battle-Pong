#include "Gui/IntroState/MultiplayerPanel.h"
#include "Events/EventManager.h"
#include "Events/Click.h"
#include "Gui/ButtonId.h"
#include <SFML/Network.hpp>
MultiplayerPanel::MultiplayerPanel():
CustomPanel::CustomPanel()
{

    //Create host button
    hostButton = tgui::Button::create("Host");
    hostButton->onPress([](){
        EventManager::inst().Post<Click>(Button::id::HOST);
    });
    
    tgui::Panel::Ptr spacer2 = tgui::Panel::create();
    spacer2->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    layout1->add(spacer2); 
    layout1->add(hostButton);
    tgui::Panel::Ptr spacer3 = tgui::Panel::create();
    spacer3->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    layout1->add(spacer3);

    //Create connect button
    connectButton = tgui::Button::create("Connect");
    connectButton->onPress([](){
        EventManager::inst().Post<Click>(Button::id::CONNECT);
    });
    
    tgui::Panel::Ptr spacer4 = tgui::Panel::create();
    spacer4->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    layout3->add(spacer4); 
    layout3->add(connectButton);
    tgui::Panel::Ptr spacer5 = tgui::Panel::create();
    spacer5->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    layout3->add(spacer5);
    
    //Create back button
    backBtn = tgui::Button::create("Back");
    buttonLayout->add(backBtn);
    backBtn->onPress([](){
        EventManager::inst().Post<Click>(Button::id::INTRO_PANEL);
    });
    
    //Create spacer  
    tgui::Panel::Ptr spacer6 = tgui::Panel::create();
    spacer6->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    buttonLayout->add(spacer6);

    //Create Spacer 
    tgui::Panel::Ptr spacer7 = tgui::Panel::create();
    spacer7->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    buttonLayout->add(spacer7); 
}

MultiplayerPanel::~MultiplayerPanel()
{

}
