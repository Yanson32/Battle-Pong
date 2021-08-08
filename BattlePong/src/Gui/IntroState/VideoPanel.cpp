#include "Gui/IntroState/VideoPanel.h"
#include "Events/EventManager.h"
#include "Macros.h"
#include "Settings.h"
#include <GameUtilities/Event/OnComboChanged.h>
#include "Gui/ComboId.h"

namespace Gui
{
    VideoPanel::VideoPanel():
    OptionsPanel::OptionsPanel(sf::String("Video"))
    {
        tgui::Label::Ptr themeLabel = tgui::Label::create("Theme");
        layout2->add(themeLabel);
        
        themeCombo = tgui::ComboBox::create();
        themeCombo->addItem("Default");
        themeCombo->addItem("Black");
        themeCombo->addItem("Blue");
        //themeCombo->setSelectedItem(Settings::game.ai.toAnsiString());
        //themeCombo->setEnabled(!isPlaying); 
        themeCombo->setSelectedItem(Settings::theme); 
        themeCombo->onItemSelect([&](){
            std::string theme = themeCombo->getSelectedItem().toAnsiString();
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
        layout2->add(themeCombo);
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
