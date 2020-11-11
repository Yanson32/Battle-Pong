#include "Gui/IntroPanel.h"
#include "Settings.h"
#include "Event/Object.h"
#include "Event/Manager.h"
#include "State/Id.h"
namespace Gui
{
    IntroPanel::IntroPanel()
    {
        //ctor
        const sf::Vector2f buttonPos1(300, 400);
        const sf::Vector2f buttonPos2(300, 475);
        //ctor
        startBtn = tgui::Button::create("Start");
        startBtn->setTextSize(buttonTextSize);
        startBtn->setSize(Settings::buttonSize);
        startBtn->connect("pressed", [](){
            Event::Object event(Event::Object::Type::BUTTON_PRESSED);
            event.buttonPressed.id = Event::ButtonPressed::START_BUTTON;
            Event::Manager::inst().push(event);
        });

        optionsBtn = tgui::Button::create("Options");
        optionsBtn->setTextSize(buttonTextSize);
        optionsBtn->setSize(Settings::buttonSize);
        optionsBtn->connect("pressed", [](){
            Event::Object event(Event::Object::Type::BUTTON_PRESSED);
            event.buttonPressed.id = Event::ButtonPressed::OPTIONS_BUTTON;
            Event::Manager::inst().push(event);
        });


        layout5->add(spacer);
        layout5->add(startBtn);
        layout5->add(spacer);

        buttonLayout->add(spacer);
        buttonLayout->add(optionsBtn);
        buttonLayout->add(spacer);

    }

    IntroPanel::~IntroPanel()
    {
        //dtor
    }
}
