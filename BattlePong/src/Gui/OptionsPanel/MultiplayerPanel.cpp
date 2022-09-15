#include "Gui/OptionsPanel/MultiplayerPanel.h"
#include "Events/EventManager.h"
#include <GameUtilities/Event/Click.h>
#include "Gui/GuiId.h"
#include <SFML/Network.hpp>


namespace Gui
{

    MultiplayerPanel::MultiplayerPanel():
    CustomPanel::CustomPanel()
    {

        //Create host button
        hostButton = tgui::Button::create("Host");
        hostButton->onPress([](){
            EventManager::inst().post<GU::Evt::Click>(Gui::id::HOST);
        });
        tgui::HorizontalLayout::Ptr layout1 = tgui::HorizontalLayout::create();
        tgui::Panel::Ptr spacer2 = tgui::Panel::create();
        spacer2->getRenderer()->setBackgroundColor(sf::Color::Transparent);
        layout1->add(spacer2); 
        layout1->add(hostButton);
        tgui::Panel::Ptr spacer3 = tgui::Panel::create();
        spacer3->getRenderer()->setBackgroundColor(sf::Color::Transparent);
        layout1->add(spacer3);
        getContentPane()->append(layout1);

        //Create connect button
        connectButton = tgui::Button::create("Connect");
        connectButton->onPress([](){
            EventManager::inst().post<GU::Evt::Click>(Gui::id::CONNECT);
        });
        getContentPane()->append(tgui::HorizontalLayout::create()); 
        
        tgui::HorizontalLayout::Ptr layout2 = tgui::HorizontalLayout::create();
        
        tgui::Panel::Ptr spacer4 = tgui::Panel::create();
        spacer4->getRenderer()->setBackgroundColor(sf::Color::Transparent);
        layout2->add(spacer4); 
        layout2->add(connectButton);
        tgui::Panel::Ptr spacer5 = tgui::Panel::create();
        spacer5->getRenderer()->setBackgroundColor(sf::Color::Transparent);
        layout2->add(spacer5);
        getContentPane()->append(layout2); 
        
        tgui::HorizontalLayout::Ptr layout3 = tgui::HorizontalLayout::create();
        
        //Create spacer  
        tgui::Panel::Ptr spacer6 = tgui::Panel::create();
        spacer6->getRenderer()->setBackgroundColor(sf::Color::Transparent);
        buttonLayout->add(spacer6);
        
        
        //Create back button
        backBtn = tgui::Button::create("Back");
        buttonLayout->add(backBtn);
        backBtn->onPress([](){
            EventManager::inst().post<GU::Evt::Click>(Gui::id::MULTIPLAYER_PANEL_BACK);
        });
        

        //Create Spacer 
        tgui::Panel::Ptr spacer7 = tgui::Panel::create();
        spacer7->getRenderer()->setBackgroundColor(sf::Color::Transparent);
        buttonLayout->add(spacer7); 
    }


    void MultiplayerPanel::init(const int &width, const int &height)
    {
        this->setSize(width / 2, height / 2);
        this->setPosition(width / 4, height / 4);
    }


    MultiplayerPanel::~MultiplayerPanel()
    {

    }
}
