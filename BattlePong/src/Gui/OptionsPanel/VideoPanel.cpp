#include "Gui/OptionsPanel/VideoPanel.h"
#include "Events/EventManager.h"
#include "Macros.h"
#include "Settings.h"
#include <GameUtilities/Event/OnComboChanged.h>
#include "Gui/ComboId.h"
#include <sstream>
namespace Gui
{
    VideoPanel::VideoPanel():
    OptionsPanel::OptionsPanel(sf::String("Video"))
    {
        getContentPane()->appendSpace();

        //Theme selection box
        themeCombo = tgui::ComboBox::create();
        themeCombo->addItem("Default");
        themeCombo->addItem("Black");
        themeCombo->addItem("Blue");
        themeCombo->setSelectedItem(Settings::theme);
        themeCombo->onItemSelect([&](){
            std::string theme = themeCombo->getSelectedItem().toStdString();
            if(theme == "Default")
            {
                EventManager::inst().Post<GU::Evt::OnComboChanged>(Gui::Combo::comboId::THEME, 0);
            }
            else if(theme == "Black")
            {
                EventManager::inst().Post<GU::Evt::OnComboChanged>(Gui::Combo::comboId::THEME, 1);
            }
            else if(theme == "Blue")
            {
                EventManager::inst().Post<GU::Evt::OnComboChanged>(Gui::Combo::comboId::THEME, 2);
            }

        });
        getContentPane()->append("Theme", themeCombo);

        //Background
        backgroundCombo = tgui::ComboBox::create();
        backgroundCombo->addItem("Star");
        backgroundCombo->addItem("Nebula");
        backgroundCombo->setSelectedItem(Settings::background);
        backgroundCombo->onItemSelect([&]()
        {
            std::string background = backgroundCombo->getSelectedItem().toStdString();
            if(background == "Star")
                EventManager::inst().Post<GU::Evt::OnComboChanged>(Gui::Combo::comboId::BACKGROUND, 0);
            else if(background == "Nebula")
                EventManager::inst().Post<GU::Evt::OnComboChanged>(Gui::Combo::comboId::BACKGROUND, 1);

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

        resolutionCombo->setSelectedItem(Settings::theme);
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
