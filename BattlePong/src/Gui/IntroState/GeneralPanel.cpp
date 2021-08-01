#include "Gui/IntroState/GeneralPanel.h"
//#include "Event/Object.h"
//#include "Event/Manager.h"
#include "Macros.h"

namespace Gui
{
    GeneralPanel::GeneralPanel(DebugDraw *debugDraw):
    OptionsPanel::OptionsPanel(sf::String("General"))
    {
        UNUSED(debugDraw); 
        comboLable = tgui::Label::create("Time Limit");
        comboLable->setPosition({0, 100});

        comboBox = tgui::ComboBox::create();
        comboBox->setPosition({100, 100});
        comboBox->addItem("30");
        comboBox->addItem("45");
        comboBox->addItem("60");
        comboBox->setSelectedItem("30");
        comboBox->onItemSelect([&](){
//            sf::String text = comboBox->getSelectedItem();
//            Event::Object event(Event::Object::Type::TIME_CHANGED);
//
//            if(text == "30")
//                event.timeChanged.time = 30;
//            else if(text == "45")
//                event.timeChanged.time = 45;
//            else if(text == "60")
//                event.timeChanged.time = 60;
//
//            Event::Manager::inst().push(event);
        });

        aiLable = tgui::Label::create("Ai");
        aiLable->setPosition({0, 150});

        aiCombo = tgui::ComboBox::create();
        aiCombo->setPosition({100, 150});
        aiCombo->addItem("Easy");
        aiCombo->addItem("Medium");
        aiCombo->addItem("Hard");
        aiCombo->setSelectedItem("Medium");
        aiCombo->onItemSelect([&](){
//            sf::String text = comboBox->getSelectedItem();
//            Event::Object event(Event::Object::Type::AI_CHANGED);
//            Event::Manager::inst().push(event);
        });

        tgui::HorizontalLayout::Ptr timerLayout = tgui::HorizontalLayout::create();
        timerLayout->setPosition(0, 100);
        timerLayout->setSize("100%", "10%");
        layout2->add(comboLable);
        layout2->add(comboBox);
        this->add(timerLayout);

        tgui::HorizontalLayout::Ptr aiLayout = tgui::HorizontalLayout::create();
        aiLayout->setPosition(0, 150);
        aiLayout->setSize("100%", "10%");
        layout3->add(aiLable);
        layout3->add(aiCombo);
        this->add(aiLayout);

    }
    void GeneralPanel::init(const int &width, const int &height)
    {
        tabs->select("General");
        this->setSize(width / 2, height / 2);
        this->setPosition(width / 4, height / 4);
    }
    GeneralPanel::~GeneralPanel()
    {

    }
}
