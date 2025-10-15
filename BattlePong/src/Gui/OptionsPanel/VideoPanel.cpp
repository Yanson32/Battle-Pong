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
        themeComboBox= tgui::ComboBox::create();
        for(auto &element: Settings::themes)
            themeComboBox->addItem(element);
        
        themeComboBox->setSelectedItem(Settings::currentTheme);
        themeComboBox->setChangeItemOnScroll(true);
        themeComboBox->onItemSelect([&](){
            EventManager::inst().post<GU::Evt::OnItemSelected>(themeComboBox, Gui::id::THEME, themeComboBox->getSelectedItemIndex());
        });
        getContentPane()->append("Theme", themeComboBox);

        //Background
        backgroundComboBox = tgui::ComboBox::create();
        for(auto &element : Settings::backgrounds)
            backgroundComboBox->addItem(element);
        backgroundComboBox->setSelectedItem(Settings::currentBackground);
        backgroundComboBox->setChangeItemOnScroll(true);
        backgroundComboBox->onItemSelect([&]()
        {
            EventManager::inst().post<GU::Evt::OnItemSelected>(backgroundComboBox, Gui::id::BACKGROUND, backgroundComboBox->getSelectedItemIndex());
        });
        getContentPane()->append("Background", backgroundComboBox);

        //Resolution
        resolutionComboBox = tgui::ComboBox::create();

        std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
        for (std::size_t i = 0; i < modes.size(); ++i)
        {
            sf::VideoMode mode = modes[i];
            std::stringstream ss;
            ss << mode.width;
            ss << " x ";
            ss << mode.height;

            resolutionComboBox->addItem(ss.str());
        }

        std::stringstream dss;
        dss << Settings::dimensions.x;
        dss << " x ";
        dss << Settings::dimensions.y;

        resolutionComboBox->setSelectedItem(dss.str());
        resolutionComboBox->setChangeItemOnScroll(true);
        resolutionComboBox->onItemSelect([&](){
            std::stringstream ss(resolutionComboBox->getSelectedItem().toStdString());
            std::string trash;
            ss >> Settings::dimensions.x;
            ss >> trash;
            ss >> Settings::dimensions.y;
            BP_LOG_WARNING("Resolution changed the system may need to be restarted");
            EventManager::inst().post<GU::Evt::OnItemSelected>(resolutionComboBox, Gui::id::RESOLUTION, resolutionComboBox->getSelectedItemIndex());
        });
        getContentPane()->append("Resolution", resolutionComboBox);
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
