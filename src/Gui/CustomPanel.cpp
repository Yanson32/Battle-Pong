#include "Gui/CustomPanel.h"
#include "Settings.h"
namespace Gui
{
    CustomPanel::CustomPanel()
    {
        //ctor

		spacer = tgui::Panel::create();
		spacer->getRenderer()->setBackgroundColor(sf::Color::Transparent);

        this->setSize({Settings::inst().screen.x / 2, Settings::inst().screen.y / 2});
        this->setPosition({Settings::inst().screen.x / 4, Settings::inst().screen.y / 4});
        this->getRenderer()->setBackgroundColor(sf::Color::Transparent);

        mainLayout = tgui::VerticalLayout::create();
        this->add(mainLayout);
        mainLayout->setSize("100%", "100%");
        tabLayout = tgui::HorizontalLayout::create();
        tabLayout->setSize("100%", "20%");
        mainLayout->add(tabLayout);
        layout1 = tgui::HorizontalLayout::create();
        layout1->setSize("100%", "10%");
        mainLayout->add(layout1);
        layout2 = tgui::HorizontalLayout::create();
        layout2->setSize("100%", "10%");
        mainLayout->add(layout2);
        layout3 = tgui::HorizontalLayout::create();
        layout3->setSize("100%", "10%");
        mainLayout->add(layout3);
        layout4 = tgui::HorizontalLayout::create();
        layout4->setSize("100%", "10%");
        mainLayout->add(layout4);
        layout5 = tgui::HorizontalLayout::create();
        layout5->setSize("100%", "10%");
        mainLayout->add(layout5);
        layout6 = tgui::HorizontalLayout::create();
        layout6->setSize("100%", "10%");
        mainLayout->add(layout6);
        buttonLayout = tgui::HorizontalLayout::create();
        buttonLayout->setSize("100%", "20%");
        mainLayout->add(buttonLayout);
    }

    CustomPanel::~CustomPanel()
    {
        //dtor
    }
}
