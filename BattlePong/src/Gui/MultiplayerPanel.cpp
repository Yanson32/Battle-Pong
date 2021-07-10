#include "Gui/MultiplayerPanel.h"
#include "Events/EventManager.h"
#include "Events/Click.h"
#include "Gui/ButtonId.h"
#include <SFML/Network.hpp>
MultiplayerPanel::MultiplayerPanel():
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
//            Event::Object event(Event::Object::Type::BUTTON_PRESSED);
//            event.buttonPressed.id = Event::ButtonPressed::BACK_BUTTON;
//            Event::Manager::inst().push(event);
        EventManager::inst().Post<Click>(Button::id::INTRO_PANEL);
    });

    //Create ip label
    ipLabel = tgui::Label::create("Ip");;
    layout4->add(ipLabel);

    //Create ip edit box
    ipBox = tgui::EditBox::create();
    layout4->add(ipBox);

    buttonLayout->add(backBtn);

    //Create host button
    hostButton = tgui::Button::create("Host");
    buttonLayout->add(hostButton);

    //Create connect button
    connectButton = tgui::Button::create("Connect");
    connectButton->setEnabled(false);
    buttonLayout->add(connectButton);
}

MultiplayerPanel::~MultiplayerPanel()
{

}
