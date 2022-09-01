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

        this->setSize({Settings::dimensions.x / 2, Settings::dimensions.y / 2});
        this->setPosition({Settings::dimensions.x / 4, Settings::dimensions.y / 4});
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
        layout->setSize("100% - 50", HEIGHT);
        layout->setPosition(25, count * HEIGHT); 
        ++count;
        add(layout);
        return true;
    }


    void ContentPane::appendHeader(const tgui::String &header)
    {

        //Create layout
        tgui::HorizontalLayout::Ptr layout = tgui::HorizontalLayout::create();
        append(layout);

        tgui::Label::Ptr label = tgui::Label::create(header);
        //label->getRenderer()->setBackgroundColor(sf::Color(100,100,100, 100));
        label->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
        label->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
        label->setTextSize(20);
        layout->add(label);

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
        //Create layout
        tgui::HorizontalLayout::Ptr layout = tgui::HorizontalLayout::create();
        append(layout);

        tgui::Label::Ptr label = tgui::Label::create("");
        layout->add(label);
    }

    ContentPane::~ContentPane()
    {

    }
}
