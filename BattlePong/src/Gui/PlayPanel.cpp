#include "Gui/PlayPanel.h"
#include "Gui/ButtonId.h"
#include "Events/EventManager.h"
#include "Events/Click.h"
#include <SFML/Network.hpp>
PlayPanel::PlayPanel():
 Gui::CustomPanel()
{
   tgui::Panel::Ptr spacer = tgui::Panel::create(""); 
   spacer->getRenderer()->setBackgroundColor(sf::Color::Transparent); 
   buttonLayout->add(spacer);
   
   tgui::Button::Ptr backButton = tgui::Button::create("Back"); 
    backButton->onPress([](){
        EventManager::inst().Post<Click>(Button::id::BACK_INTRO_STATE);
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
