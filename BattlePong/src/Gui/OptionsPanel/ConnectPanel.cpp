#include "Gui/OptionsPanel/ConnectPanel.h"
#include "Events/EventManager.h"
#include <GameUtilities/Event/Events/Mouse/OnClick.h>
#include "Gui/GuiId.h"
#include <SFML/Network.hpp>
#include "Settings.h"
#include "Log.h"
#include "TGUIFunctions.h"

namespace Gui
{
    ConnectPanel::ConnectPanel():
    CustomPanel::CustomPanel()
    {

        getContentPane()->appendSpace();

        //Create ip edit box
        ipBox = tgui::EditBox::create();
        ipBox->setText("192.168.88.243");
        Settings::clientIp = ipBox->getText().toStdString(); 
        getContentPane()->append("Ip", ipBox);
        
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
            EventManager::inst().post<GU::Evt::OnClick>(Gui::id::CONNECT_PANEL_BACK);
        });
        
        //Create connect button
        connectButton = tgui::Button::create("Connect");
        connectButton->onPress([this]()
        {
            Settings::isHost = false;
            Settings::multiplayer = true;
            EventManager::inst().post<GU::Evt::OnClick>(Gui::id::START);
                 
        });
        buttonLayout->add(connectButton);
        
        //Add back button 
        buttonLayout->add(backBtn);
        
        //Add spacer
        buttonLayout->add(spacer);
    }




    void ConnectPanel::init(const int &width, const int &height)
    {
        this->setSize(width / 2, height / 2);
        this->setPosition(width / 4, height / 4);
    }

    ConnectPanel::~ConnectPanel()
    {

    }
}
