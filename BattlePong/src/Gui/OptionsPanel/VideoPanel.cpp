#include "Gui/OptionsPanel/VideoPanel.h"
#include "Events/EventManager.h"
#include "Macros.h"
#include "Settings.h"
#include <GameUtilities/Event/Events/Widget/OnItemSelected.h>
#include "Gui/GuiId.h"
#include <sstream>


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
            EventManager::inst().post<GU::Evt::OnItemSelected>(themeCombo.get(), Gui::id::THEME, themeCombo->getSelectedItemIndex());
        });
        getContentPane()->append("Theme", themeCombo);

        //Background
        backgroundCombo = tgui::ComboBox::create();
        for(auto &element : Settings::backgrounds)
            backgroundCombo->addItem(element);
        backgroundCombo->setSelectedItem(Settings::currentBackground);
        backgroundCombo->onItemSelect([&]()
        {
            EventManager::inst().post<GU::Evt::OnItemSelected>(backgroundCombo.get(), Gui::id::BACKGROUND, backgroundCombo->getSelectedItemIndex());
        });
        getContentPane()->append("Background", backgroundCombo);

        //Resolution
        resolutionCombo = tgui::ComboBox::create();
        resolutionCombo->addItem("Fulll Screen");

        std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
        for (std::size_t i = 0; i < modes.size(); ++i)
        {
            sf::VideoMode mode = modes[i];
            std::stringstream ss;
            ss << mode.width;
            ss << "x";
            ss << mode.height;

            resolutionCombo->addItem(ss.str());
        }

        //resolutionCombo->setSelectedItem(Settings::dimension);
        resolutionCombo->onItemSelect([&](){
            std::string theme = resolutionCombo->getSelectedItem().toStdString();
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
