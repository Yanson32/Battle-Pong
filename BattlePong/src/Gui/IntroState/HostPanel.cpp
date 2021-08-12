


#include "Gui/IntroState/HostPanel.h"
#include "Gui/ButtonId.h"
#include "Events/EventManager.h"
#include <GameUtilities/Event/Click.h>
#include <SFML/Network.hpp>
#include "Settings.h"

HostPanel::HostPanel():
CustomPanel::CustomPanel()
{
    //Global Ip address label
    publicIpLabel = tgui::Label::create("Public Ip");
    layout1->add(publicIpLabel);

    
    //EditBox to enter ip address
    publicIpAdress = tgui::Label::create(Settings::publicIp);
    layout1->add(publicIpAdress);

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
        EventManager::inst().Post<GU::Evt::Click>(Button::id::MULTIPLAYER);
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
