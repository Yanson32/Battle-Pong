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
    GeneralPanel::GeneralPanel(const bool isPlaying):
    OptionsPanel::OptionsPanel(sf::String("General"))
    {
        comboLable = tgui::Label::create("Time Limit");
        layout2->add(comboLable);
        
        //Create lable instead of combobox when the user is playing the game
        if(isPlaying)
        {
            tgui::Label::Ptr tLimitLabel = tgui::Label::create(Settings::game.time.toAnsiString());
            layout2->add(tLimitLabel);   
             
        }
        else
        {
            comboBox = tgui::ComboBox::create();
            comboBox->addItem("30");
            comboBox->addItem("45");
            comboBox->addItem("60");
            comboBox->setSelectedItem(Settings::game.time.toAnsiString());
            comboBox->setEnabled(!isPlaying); 
            comboBox->onItemSelect([&](){
                sf::String text = comboBox->getSelectedItem().toAnsiString();
                Settings::game.time = text; 
    //            Event::Manager::inst().push(event);
            });
            layout2->add(comboBox);
        }
        aiLable = tgui::Label::create("Ai");
        layout3->add(aiLable);

        if(isPlaying)
        {
            tgui::Label::Ptr aiSettingLabel = tgui::Label::create(Settings::game.ai.toAnsiString());
            layout3->add(aiSettingLabel);   
        }
        else
        {
            aiCombo = tgui::ComboBox::create();
            aiCombo->addItem("Easy");
            aiCombo->addItem("Medium");
            aiCombo->addItem("Hard");
            aiCombo->setSelectedItem(Settings::game.ai.toAnsiString());
            aiCombo->setEnabled(!isPlaying); 
            aiCombo->onItemSelect([&](){
                Settings::game.ai = aiCombo->getSelectedItem().toAnsiString();
            });
            layout3->add(aiCombo);
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
