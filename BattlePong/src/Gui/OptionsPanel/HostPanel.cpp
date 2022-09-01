#include "Gui/OptionsPanel/HostPanel.h"
#include "Gui/GuiId.h"
#include "Events/EventManager.h"
#include <GameUtilities/Event/Click.h>
#include <SFML/Network.hpp>
#include "Settings.h"


namespace Gui
{

    HostPanel::HostPanel():
    CustomPanel::CustomPanel()
    {
        getContentPane()->appendSpace();

        //Public ip address
        publicIpAdress = tgui::Label::create(Settings::publicIp);
        getContentPane()->append("Public Ip", publicIpAdress);

        sf::IpAddress address2 = sf::IpAddress::getLocalAddress();
        sf::String localIp = address2.toString();

        //EditBox to enter ip address
        localIpBox = tgui::Label::create(localIp.toAnsiString());
        getContentPane()->append("Local Ip", localIpBox);

        //EditBox to enter port number
        portBox = tgui::EditBox::create();
        getContentPane()->append("Port", portBox);

        //Create back button
        backBtn = tgui::Button::create("Back");
        backBtn->onPress([](){
            EventManager::inst().Post<GU::Evt::Click>(Gui::id::HOST_PANEL_BACK);
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
}
