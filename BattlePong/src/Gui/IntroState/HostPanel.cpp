#include "Gui/IntroState/HostPanel.h"
#include "Gui/ButtonId.h"
#include "Events/EventManager.h"
#include "Events/Click.h"
#include <SFML/Network.hpp>
HostPanel::HostPanel():
CustomPanel::CustomPanel()
{
    //Global Ip address label
    globalIpLabel = tgui::Label::create("Global Ip");
    layout1->add(globalIpLabel);

    sf::IpAddress address = sf::IpAddress::getPublicAddress();
    sf::String globalIp = address.toString();

    //EditBox to enter ip address
    globalIpAdress = tgui::Label::create(globalIp.toAnsiString());
    layout1->add(globalIpAdress);

    //Local Ip address label
    localIpLabel = tgui::Label::create("Local Ip");
    layout2->add(localIpLabel);

    sf::IpAddress address2 = sf::IpAddress::getLocalAddress();
    sf::String localIp = address2.toString();

    //EditBox to enter ip address
    localIpBox = tgui::Label::create(localIp.toAnsiString());
    layout2->add(localIpBox);

    //Port number lable
    portLabel = tgui::Label::create("Port");
    layout3->add(portLabel);

    //EditBox to enter port number
    portBox = tgui::EditBox::create();
    layout3->add(portBox);
    
    //Create back button
    backBtn = tgui::Button::create("Back");
    backBtn->onPress([](){
        EventManager::inst().Post<Click>(Button::id::MULTIPLAYER);
    });
   
    //Create host button   
    hostButton = tgui::Button::create("Host");
    hostButton->setEnabled(false);
    buttonLayout->add(hostButton);
   
    //Create back button 
    buttonLayout->add(backBtn);

    //Create spacer 
    buttonLayout->add(spacer);
    
}


void HostPanel::init(const int &width, const int &height)
{
    this->setSize(width / 2, height / 2);
    this->setPosition(width / 4, height / 4);
}


HostPanel::~HostPanel()
{

}
