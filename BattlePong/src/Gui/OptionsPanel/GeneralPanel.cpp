#include "Gui/OptionsPanel/GeneralPanel.h"
//#include "Event/Object.h"
#include "Events/EventManager.h"
#include "Macros.h"
#include "Settings.h"
#include <GameUtilities/Event/Events/Widget/OnItemSelected.h>
#include <GameUtilities/Event/Events/Widget/OnCheck.h>
#include <GameUtilities/Core/PreferencesManager.h>
#include "Gui/GuiId.h"
#include "TGUIFunctions.h"

namespace Gui
{
    GeneralPanel::GeneralPanel(const StateId state):
    OptionsPanel::OptionsPanel(sf::String("General"))
    {
        getContentPane()->appendSpace();
        
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
            aiCombo->setChangeItemOnScroll(true);
            aiCombo->setSelectedItem(toTguiString(Settings::ai));
            aiCombo->onItemSelect([&](){
                Settings::ai = aiCombo->getSelectedItem().toStdString();
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
