#include "Gui/HostPanel.h"
#include "Gui/ButtonId.h"
#include "Events/EventManager.h"
#include "Events/Click.h"
#include <SFML/Network.hpp>
HostPanel::HostPanel():
CustomPanel::CustomPanel()
{
    //Create back button
    backBtn = tgui::Button::create("Back");
    backBtn->onPress([](){
        EventManager::inst().Post<Click>(Button::id::MULTIPLAYER);
    });
    buttonLayout->add(spacer);
    buttonLayout->add(backBtn);

    //Port number lable
    portLabel = tgui::Label::create("Port");
    layout1->add(portLabel);
    
    
    //EditBox to enter port number
    portBox = tgui::EditBox::create();
    layout1->add(portBox);
    

    hostButton = tgui::Button::create("Host");
    hostButton->setEnabled(false);
    buttonLayout->add(hostButton);
    
    
    buttonLayout->add(spacer);
    
    //setBackgroundColor(sf::Color::Transparent);

}

HostPanel::~HostPanel()
{

}
