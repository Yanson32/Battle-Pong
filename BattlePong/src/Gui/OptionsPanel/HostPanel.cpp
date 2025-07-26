#include "Gui/OptionsPanel/HostPanel.h"
#include "Gui/GuiId.h"
#include "Events/EventManager.h"
#include <GameUtilities/Event/Events/Mouse/OnClick.h>
#include <SFML/Network.hpp>
#include "Settings.h"
#include "Log.h"

namespace Gui
{

    HostPanel::HostPanel():
    CustomPanel::CustomPanel()
    {
        getContentPane()->appendSpace();

        //Public ip address
        publicIpAdress = tgui::Label::create(Settings::publicIp.getString());
        getContentPane()->append("Public Ip", publicIpAdress);

        sf::IpAddress address2 = sf::IpAddress::getLocalAddress();
        sf::String localIp = address2.toString();

        //EditBox to enter ip address
        localIpBox = tgui::Label::create(localIp.toAnsiString());
        getContentPane()->append("Local Ip", localIpBox);

        //EditBox to enter port number
        portBox = tgui::EditBox::create();
        portBox->setText(std::to_string(Settings::port));
        portBox->onTextChange([this](){
            if(!portBox->getText().attemptToInt(Settings::port))
            {
                BP_LOG_ERROR("Unable to change port");
            }
        });
        getContentPane()->append("Port", portBox);

        //Create back button
        backBtn = tgui::Button::create("Back");
        backBtn->onPress([](){
            EventManager::inst().post<GU::Evt::OnClick>(Gui::id::HOST_PANEL_BACK);
        });

        //Create host button
        hostButton = tgui::Button::create("Host");
        hostButton->onPress([](){
            Settings::isHost = true;
            Settings::multiplayer = true;
            EventManager::inst().post<GU::Evt::OnClick>(Gui::id::START);
        });
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
