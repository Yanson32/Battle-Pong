#include "Gui/IntroState/ConnectPanel.h"
#include "Events/EventManager.h"
#include <GameUtilities/Event/Click.h>
#include "Gui/ButtonId.h"
#include <SFML/Network.hpp>
ConnectPanel::ConnectPanel():
CustomPanel::CustomPanel()
{

    getContentPane()->appendSpace();

    //Create ip edit box
    ipBox = tgui::EditBox::create();
    ipBox->onTextChange(&ConnectPanel::onTextChanged, this);
    getContentPane()->append("Ip", ipBox);
    
    //EditBox to enter port number
    portBox = tgui::EditBox::create();
    portBox->onTextChange(&ConnectPanel::onTextChanged, this);
    getContentPane()->append("Port", portBox);
    
    //Create back button
    backBtn = tgui::Button::create("Back");
    backBtn->onPress([](){
        EventManager::inst().Post<GU::Evt::Click>(Button::id::CONNECT_PANEL_BACK);
    });
    
    //Create connect button
    connectButton = tgui::Button::create("Connect");
    connectButton->setEnabled(false);
    buttonLayout->add(connectButton);
    
    //Add back button 
    buttonLayout->add(backBtn);
    
    //Add spacer
    buttonLayout->add(spacer);
}


void ConnectPanel::onTextChanged()
{
    connectButton->setEnabled(false);

    if(ipBox->getText() !=  "")
    {
        if(portBox->getText() != "")
        {
            connectButton->setEnabled(true);
        } 
    }

}


void ConnectPanel::init(const int &width, const int &height)
{
    this->setSize(width / 2, height / 2);
    this->setPosition(width / 4, height / 4);
}

ConnectPanel::~ConnectPanel()
{

}
