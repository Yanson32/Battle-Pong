#include "Gui/IntroState/GeneralPanel.h"
//#include "Event/Object.h"
#include "Events/EventManager.h"
#include "Macros.h"
#include "Settings.h"
#include <GameUtilities/Event/OnComboChanged.h>
#include <GameUtilities/Event/OnCheck.h>
#include <GameUtilities/Core/PreferencesManager.h>
#include "Gui/ComboId.h"
#include "TGUIFunctions.h"

namespace Gui
{
    GeneralPanel::GeneralPanel(const StateId state):
    OptionsPanel::OptionsPanel(sf::String("General"))
    {
        getContentPane()->appendSpace();

        //Create lable instead of combobox when the user is playing the game
        if(state == StateId::PLAY_STATE)
        {
            tgui::Label::Ptr tLimitLabel = tgui::Label::create(toTguiString(Settings::time));
            getContentPane()->append("Time Limit", tLimitLabel);
        }
        else
        {
            comboBox = tgui::ComboBox::create();
            comboBox->addItem("30");
            comboBox->addItem("45");
            comboBox->addItem("60");
            comboBox->setSelectedItem(toTguiString(Settings::time));
            comboBox->onItemSelect([&](){
                Settings::time  = comboBox->getSelectedItem().toStdString();
                GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                prefMan.write("ResetTime", Settings::time.toAnsiString());
            });
            getContentPane()->append("Time Limit", comboBox);
        }

        if(state == StateId::PLAY_STATE)
        {
            tgui::Label::Ptr aiSettingLabel = tgui::Label::create(toTguiString(Settings::ai));
            getContentPane()->append("Ai", aiSettingLabel);
        }
        else
        {
            aiCombo = tgui::ComboBox::create();
            aiCombo->addItem("Easy");
            aiCombo->addItem("Medium");
            aiCombo->addItem("Hard");
            aiCombo->setSelectedItem(toTguiString(Settings::ai));
            aiCombo->onItemSelect([&](){
                Settings::ai = aiCombo->getSelectedItem().toStdString();
                GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
                prefMan.write("Difficulty", Settings::ai.toAnsiString());
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
