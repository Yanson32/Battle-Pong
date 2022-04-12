#include "Gui/PlayPanel.h"
#include "Gui/ButtonId.h"
#include "Events/EventManager.h"
#include <GameUtilities/Event/Click.h>
#include <SFML/Network.hpp>
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
        Button::id id;
        if(text == "General")
            id =  Button::id::GENERAL_TAB;
        else if(text == "Controls")
            id = Button::id::CONTROLS_TAB;
        else if(text == "Sound")
            id = Button::id::SOUND_TAB;
        else if(text == "Dev")
            id = Button::id::DEV_TAB;

        EventManager::inst().Post<GU::Evt::Click>(id);
    });

   tgui::Panel::Ptr spacer = tgui::Panel::create("");
   spacer->getRenderer()->setBackgroundColor(sf::Color::Transparent);
   buttonLayout->add(spacer);

   tgui::Button::Ptr backButton = tgui::Button::create("Back");
    backButton->onPress([](){
        EventManager::inst().Post<GU::Evt::Click>(Button::id::INTRO_PANEL);
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
