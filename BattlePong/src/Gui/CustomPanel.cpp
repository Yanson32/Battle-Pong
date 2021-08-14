#include "Gui/CustomPanel.h"
#include "Settings.h"
#include <iostream>

namespace Gui
{
    CustomPanel::CustomPanel()
    {
        //ctor

		spacer = tgui::Panel::create();
		spacer->getRenderer()->setBackgroundColor(sf::Color::Transparent);

        this->setSize({Settings::window.dimensions.x / 2, Settings::window.dimensions.y / 2});
        this->setPosition({Settings::window.dimensions.x / 4, Settings::window.dimensions.y / 4});
        this->getRenderer()->setBackgroundColor(sf::Color::Transparent);

        //Create the main layout
        mainLayout = tgui::VerticalLayout::create();
        mainLayout->setSize("100%", "100%");
        this->add(mainLayout);
       
        //Create tab layout 
        tabLayout = tgui::HorizontalLayout::create();
        tabLayout->setSize("100%", "10%");
        add(tabLayout);
        
        //Create the content pane 
        contentPane.reset(new ContentPane()); 
        contentPane->setSize("100%", "80%"); 
        contentPane->setPosition(0, "10%"); 
        contentPane->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
        contentPane->getRenderer()->setBackgroundColor(sf::Color::Transparent); 
        add(contentPane); 

        //Create button layout
        buttonLayout = tgui::HorizontalLayout::create();
        buttonLayout->setSize("100%", "10%");
        buttonLayout->setPosition(0, "90%"); 
        add(buttonLayout);
    }
    
    
    void CustomPanel::resize(const int &width, const int &height)
    {
        this->setSize(width / 2, height / 2);
        this->setPosition(width / 4, height / 4); 
    }

    std::shared_ptr<ContentPane> CustomPanel::getContentPane()
    {
       return contentPane; 
    }

    CustomPanel::~CustomPanel()
    {
        //dtor
    }
    
    

    ContentPane::ContentPane()
    {
    }


    
    bool ContentPane::append(const tgui::String &label, std::shared_ptr<tgui::Widget> widget)
    {
        
        //Create layout 
        tgui::HorizontalLayout::Ptr layout = tgui::HorizontalLayout::create();
        append(layout);

        //Create label
        layout->add(tgui::Label::create(label)); 
        
        //Add widget to layout 
        layout->add(widget, label);
        
        return true; 
    }
   
    bool ContentPane::append(tgui::HorizontalLayout::Ptr layout)
    {
        //layouts.push_back(layout);
        layout->setSize("100%", HEIGHT);
        layout->setPosition(0, count * HEIGHT); 
        ++count; 
        add(layout); 
        return true;
    }


    void ContentPane::appendHeader(const tgui::String &header)
    {
        
        //Create layout 
        tgui::HorizontalLayout::Ptr layout = tgui::HorizontalLayout::create();
        append(layout);
        
        layout->addSpace(1);

        //Create label
        layout->add(tgui::Label::create(header)); 
       
        layout->addSpace(1); 
    }
    
    void ContentPane::append(const tgui::String &label, std::shared_ptr<tgui::CheckBox> check)
    {
        tgui::HorizontalLayout::Ptr layout = tgui::HorizontalLayout::create();
        append(layout);

        tgui::Panel::Ptr panel1 = tgui::Panel::create();
        panel1->getRenderer()->setBackgroundColor(sf::Color::Transparent); 
        panel1->add(tgui::Label::create(label));

        tgui::Panel::Ptr panel2 = tgui::Panel::create();
        panel2->getRenderer()->setBackgroundColor(sf::Color::Transparent); 
        panel2->add(check);

        layout->add(panel1);
        layout->add(panel2);
    }


    void ContentPane::appendSpace()
    {
       appendHeader(""); 
    }

    ContentPane::~ContentPane()
    {

    }
}
