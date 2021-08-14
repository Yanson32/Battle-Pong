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
        publicIp = tgui::Label::create(Settings::publicIp);
        getContentPane()->append("Public Ip", publicIp); 
        
        localIp = tgui::Label::create(Settings::localIp);
        getContentPane()->append("Local Ip", localIp); 
        
        portBox = tgui::Label::create(Settings::port);
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
