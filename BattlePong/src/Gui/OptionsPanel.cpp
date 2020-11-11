#include "Gui/OptionsPanel.h"
#include "Events/EventManager.h"
#include "Events/EventBase.h"
#include "Events/Click.h"
#include "Gui/ButtonId.h"
namespace Gui
{
    OptionsPanel::OptionsPanel(const sf::String &tab)
    {

    tabs = tgui::Tabs::create();
    tabLayout->add(tabs);
    //tabs->setPosition({300, 100});
    tabs->add("General");
    tabs->add("Controls");
    tabs->add("Sound");
    #ifdef DEBUG
        tabs->add("Dev");
    #endif
    tabs->select(tab);
    tabs->setTabVisible(0, true);
    tabs->connect("TabSelected", [&](){
        sf::String text = tabs->getSelected();
        Button::id id;
        if(text == "General")
            id = Button::id::GENERAL_TAB;
        else if(text == "Controls")
            id = Button::id::CONTROLS_TAB;
        else if(text == "Sound")
            id = Button::id::SOUND_TAB;
        else if(text == "Dev")
            id = Button::id::DEV_TAB;

        EventManager::inst().Post<Click>(id);
    });




    backBtn = tgui::Button::create("Back");
    backBtn->connect("pressed", [](){
//            Event::Object event(Event::Object::Type::BUTTON_PRESSED);
//            event.buttonPressed.id = Event::ButtonPressed::BACK_BUTTON;
//            Event::Manager::inst().push(event);
        EventManager::inst().Post<Click>(Button::id::INTRO_PANEL);
    });


    buttonLayout->add(spacer);
    buttonLayout->add(backBtn);
    buttonLayout->add(spacer);

    }

    OptionsPanel::~OptionsPanel()
    {

    }
}
