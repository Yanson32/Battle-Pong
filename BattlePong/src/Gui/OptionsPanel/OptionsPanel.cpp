#include "Gui/OptionsPanel/OptionsPanel.h"
#include "Events/EventManager.h"
#include "Events/EventBase.h"
#include <GameUtilities/Event/Click.h>
#include "Gui/GuiId.h"

namespace GU
{
    namespace Gui
    {
        OptionsPanel::OptionsPanel(const sf::String &tab)
        {
            tabs = tgui::Tabs::create();
            tabLayout->add(tabs);
            tabs->add("General");
            tabs->add("Controls");
            tabs->add("Video");
            tabs->add("Sound");
            tabs->add("Network");
            #ifdef DEBUG
                tabs->add("Dev");
            #endif
            tabs->select(tab.toAnsiString());
            tabs->setTabVisible(0, true);
            tabs->onTabSelect([&](){
                sf::String text = tabs->getSelected().toStdString();
                GU::Gui::id id;
                if(text == "General")
                    id = GU::Gui::id::GENERAL_TAB;
                else if(text == "Controls")
                    id = GU::Gui::id::CONTROLS_TAB;
                else if(text == "Video")
                    id = GU::Gui::id::VIDEO_TAB;
                else if(text == "Sound")
                    id = GU::Gui::id::SOUND_TAB;
                else if(text == "Network")
                    id = GU::Gui::id::NETWORK_TAB;
                else if(text == "Dev")
                    id = GU::Gui::id::DEV_TAB;
                EventManager::inst().Post<GU::Evt::Click>(id);
            });


            backBtn = tgui::Button::create("Back");
            backBtn->onPress([](){
                EventManager::inst().Post<GU::Evt::Click>(GU::Gui::id::OPTIONS_PANEL_BACK);
            });


            buttonLayout->add(spacer);
            buttonLayout->add(backBtn);

            //Create spacer
            tgui::Panel::Ptr spacer2 = tgui::Panel::create();
            spacer2->getRenderer()->setBackgroundColor(sf::Color::Transparent);
            buttonLayout->add(spacer2);

        }

        OptionsPanel::~OptionsPanel()
        {

        }
    }
}
