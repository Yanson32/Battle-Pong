#include "Gui/OptionsPanel/NetworkPanel.h"
//#include "Event/Object.h"
#include "Events/EventManager.h"
#include "Macros.h"
#include "Settings.h"
#include <GameUtilities/Event/OnSliderChanged.h>
#include <GameUtilities/Event/OnTextChanged.h>
#include <GameUtilities/Event/PlayMusic.h>
#include "Gui/GuiId.h"
#include "Settings.h"
#include <SFML/System/String.hpp>
#include "TGUIFunctions.h"


namespace Gui
{
    NetworkPanel::NetworkPanel():
    OptionsPanel::OptionsPanel(sf::String("Network"))
    {
        getContentPane()->appendSpace();

        publicIp = tgui::Label::create(Settings::publicIp);
        getContentPane()->append("Public Ip", publicIp); 
        
        localIp = tgui::Label::create(Settings::localIp);
        getContentPane()->append("Local Ip", localIp); 
        
        portBox = tgui::EditBox::create();
        portBox->setInputValidator("[0-9]+");
        portBox->setMaximumCharacters(3);
        portBox->limitTextWidth(true);
        portBox->setText(toTguiString(Settings::port));      
        portBox->onTextChange([&](){
            if(!portBox->getText().empty())
                EventManager::inst().post<GU::Evt::OnTextChanged>(Gui::id::PORT, portBox->getText().toStdString());
        });
        getContentPane()->append("Port", portBox); 
        
    }
    void NetworkPanel::init(const int &width, const int &height)
    {
        tabs->select("Network");
        this->setSize(width / 2, height / 2);
        this->setPosition(width / 4, height / 4);
    }
    NetworkPanel::~NetworkPanel()
    {

    }
}
