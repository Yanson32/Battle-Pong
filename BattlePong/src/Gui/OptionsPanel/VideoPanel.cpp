#include "Gui/OptionsPanel/VideoPanel.h"
#include "Events/EventManager.h"
#include "Macros.h"
#include "Settings.h"
#include <GameUtilities/Event/Events/Widget/OnItemSelected.h>
#include "Gui/GuiId.h"
#include <sstream>
#include "Log.h"

namespace Gui
{
    VideoPanel::VideoPanel():
    OptionsPanel::OptionsPanel(sf::String("Video"))
    {
        getContentPane()->appendSpace();

        //Theme selection box
        themeCombo = tgui::ComboBox::create();
        for(auto &element: Settings::themes)
            themeCombo->addItem(element);
        
        themeCombo->setSelectedItem(Settings::currentTheme);
        themeCombo->onItemSelect([&](){
            EventManager::inst().post<GU::Evt::OnItemSelected>(themeCombo, Gui::id::THEME, themeCombo->getSelectedItemIndex());
        });
        getContentPane()->append("Theme", themeCombo);

        //Background
        backgroundCombo = tgui::ComboBox::create();
        for(auto &element : Settings::backgrounds)
            backgroundCombo->addItem(element);
        backgroundCombo->setSelectedItem(Settings::currentBackground);
        backgroundCombo->onItemSelect([&]()
        {
            EventManager::inst().post<GU::Evt::OnItemSelected>(backgroundCombo, Gui::id::BACKGROUND, backgroundCombo->getSelectedItemIndex());
        });
        getContentPane()->append("Background", backgroundCombo);

        //Resolution
        resolutionCombo = tgui::ComboBox::create();

        std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
        for (std::size_t i = 0; i < modes.size(); ++i)
        {
            sf::VideoMode mode = modes[i];
            std::stringstream ss;
            ss << mode.width;
            ss << " x ";
            ss << mode.height;

            resolutionCombo->addItem(ss.str());
        }

        std::stringstream dss;
        dss << Settings::dimensions.x;
        dss << " x ";
        dss << Settings::dimensions.y;

        resolutionCombo->setSelectedItem(dss.str());
    
        resolutionCombo->onItemSelect([&](){
            std::stringstream ss(resolutionCombo->getSelectedItem().toStdString());
            std::string trash;
            ss >> Settings::dimensions.x;
            ss >> trash;
            ss >> Settings::dimensions.y;
            BP_LOG_WARNING("Resolution changed the system may need to be restarted");
            
        });
        getContentPane()->append("Resolution", resolutionCombo);
    }
    void VideoPanel::init(const int &width, const int &height)
    {
        tabs->select("Video");
        this->setSize(width / 2, height / 2);
        this->setPosition(width / 4, height / 4);
    }
    VideoPanel::~VideoPanel()
    {

    }
}
