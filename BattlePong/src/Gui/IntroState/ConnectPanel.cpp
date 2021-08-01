#include "Gui/IntroState/ConnectPanel.h"
#include "Events/EventManager.h"
#include "Events/Click.h"
#include "Gui/ButtonId.h"
#include <SFML/Network.hpp>
ConnectPanel::ConnectPanel():
CustomPanel::CustomPanel()
{

    //Port number lable
    portLabel = tgui::Label::create("Port");
    layout1->add(portLabel);

    //EditBox to enter port number
    portBox = tgui::EditBox::create();
    portBox->onTextChange(&ConnectPanel::onTextChanged, this);
    layout1->add(portBox);

    //Create back button
    backBtn = tgui::Button::create("Back");
    backBtn->onPress([](){
        EventManager::inst().Post<Click>(Button::id::MULTIPLAYER);
    });

    //Create ip label
    ipLabel = tgui::Label::create("Ip");;
    layout2->add(ipLabel);

    //Create ip edit box
    ipBox = tgui::EditBox::create();
    ipBox->onTextChange(&ConnectPanel::onTextChanged, this);
    layout2->add(ipBox);
    
    buttonLayout->add(backBtn);

    //Create connect button
    connectButton = tgui::Button::create("Connect");
    connectButton->setEnabled(false);
    buttonLayout->add(connectButton);

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
