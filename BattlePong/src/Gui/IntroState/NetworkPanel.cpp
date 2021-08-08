#include "Gui/IntroState/NetworkPanel.h"
//#include "Event/Object.h"
#include "Events/EventManager.h"
#include "Macros.h"
#include "Settings.h"
#include <GameUtilities/Event/OnSliderChanged.h>
#include <GameUtilities/Event/PlayMusic.h>
#include "Gui/SliderId.h"
#include "Settings.h"

namespace Gui
{
    NetworkPanel::NetworkPanel():
    OptionsPanel::OptionsPanel(sf::String("Network"))
    {
        //Create global label
        globalIpLabel = tgui::Label::create("Global Ip");
        layout2->add(globalIpLabel);
       
        
        globalIp = tgui::Label::create(Settings::globalIp);
        layout2->add(globalIp); 
        
        //Create local ip label
        localIpLabel = tgui::Label::create("Local Ip");
        layout3->add(localIpLabel);
       
        
        localIp = tgui::Label::create(Settings::localIp);
        layout3->add(localIp); 
        
        //Create port label
        portBoxLabel = tgui::Label::create("Port");
        layout4->add(portBoxLabel);
       
        
        portBox = tgui::Label::create(Settings::port);
        layout4->add(portBox); 
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
