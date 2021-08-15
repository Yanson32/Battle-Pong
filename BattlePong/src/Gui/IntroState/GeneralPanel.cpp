#include "Gui/IntroState/GeneralPanel.h"
//#include "Event/Object.h"
#include "Events/EventManager.h"
#include "Macros.h"
#include "Settings.h"
#include <GameUtilities/Event/OnComboChanged.h>
#include <GameUtilities/Event/OnCheck.h>
#include "Gui/ComboId.h"

namespace Gui
{
    GeneralPanel::GeneralPanel(const StateId state):
    OptionsPanel::OptionsPanel(sf::String("General"))
    {
        getContentPane()->appendSpace(); 

        //Create lable instead of combobox when the user is playing the game
        if(state == StateId::PLAY_STATE)
        {
            tgui::Label::Ptr tLimitLabel = tgui::Label::create(Settings::game.time.toAnsiString());
            getContentPane()->append("Time Limit", tLimitLabel);   
        }
        else
        {
            comboBox = tgui::ComboBox::create();
            comboBox->addItem("30");
            comboBox->addItem("45");
            comboBox->addItem("60");
            comboBox->setSelectedItem(Settings::game.time.toAnsiString());
            comboBox->onItemSelect([&](){
                sf::String text = comboBox->getSelectedItem().toAnsiString();
                Settings::game.time = text; 
    //            Event::Manager::inst().push(event);
            });
            getContentPane()->append("Time Limit", comboBox);
        }

        if(state == StateId::PLAY_STATE)
        {
            tgui::Label::Ptr aiSettingLabel = tgui::Label::create(Settings::game.ai.toAnsiString());
            getContentPane()->append("Ai", aiSettingLabel);   
        }
        else
        {
            aiCombo = tgui::ComboBox::create();
            aiCombo->addItem("Easy");
            aiCombo->addItem("Medium");
            aiCombo->addItem("Hard");
            aiCombo->setSelectedItem(Settings::game.ai.toAnsiString());
            aiCombo->onItemSelect([&](){
                Settings::game.ai = aiCombo->getSelectedItem().toAnsiString();
            });
            getContentPane()->append("Ai", aiCombo);
        }
    }
    void GeneralPanel::init(const int &width, const int &height)
    {
        tabs->select("General");
        this->setSize(width / 2, height / 2);
        this->setPosition(width / 4, height / 4);
    }
    GeneralPanel::~GeneralPanel()
    {

    }
}
