#include "Gui/PlayPanel.h"
#include "Gui/GuiId.h"
#include "Events/EventManager.h"
#include <GameUtilities/Event/Click.h>
#include <GameUtilities/Event/Pop.h>
#include <SFML/Network.hpp>


namespace Gui
{

    PlayPanel::PlayPanel():
     Gui::CustomPanel()
    {
        tabs = tgui::Tabs::create();
        tabLayout->add(tabs);

        tabs->add("General");
        tabs->add("Controls");
        tabs->add("Sound");
        #ifdef DEBUG
           tabs->add("Dev");
        #endif
        //tabs->select(tab.toStdString());
        tabs->setTabVisible(0, true);
        tabs->onTabSelect([&](){
            sf::String text = tabs->getSelected().toStdString();
            Gui::id id;
            if(text == "General")
                id =  Gui::id::GENERAL_TAB;
            else if(text == "Controls")
                id = Gui::id::CONTROLS_TAB;
            else if(text == "Sound")
                id = Gui::id::SOUND_TAB;
            else if(text == "Dev")
                id = Gui::id::DEV_TAB;

            EventManager::inst().post<GU::Evt::Click>(id);
        });

       tgui::Panel::Ptr spacer = tgui::Panel::create("");
       spacer->getRenderer()->setBackgroundColor(sf::Color::Transparent);
       buttonLayout->add(spacer);

       tgui::Button::Ptr backButton = tgui::Button::create("Back");
        backButton->onPress([](){
            EventManager::inst().post<GU::Evt::Click>(Gui::id::BACK);
            });

       buttonLayout->add(backButton);



       tgui::Panel::Ptr spacer2 = tgui::Panel::create("");
       spacer2->getRenderer()->setBackgroundColor(sf::Color::Transparent);
       buttonLayout->add(spacer2);
    }


    void PlayPanel::init(const int &width, const int &height)
    {
        this->setSize(width / 2, height / 2);
        this->setPosition(width / 4, height / 4);
    }


    PlayPanel::~PlayPanel()
    {

    }
}
