#include "Gui/IntroState/DevPanel.h"
//#include "Event/Manager.h"
//#include "DebugDraw.h"
#include "Macros.h"
#include "Box2D/Box2D.h"

namespace Gui
{
	DevPanel::DevPanel():
	OptionsPanel::OptionsPanel(sf::String("Dev"))
	{
        sf::Vector2f position1(75, 0);
        sf::Vector2f position2(225, 0);
        //layout2->setSize("70%", "10%");
        //layout3->setSize("70%", "10%");
        //layout4->setSize("70%", "10%");
		//const float WIDTH = 0;
		//Create AABB checkbox
		aabb = tgui::CheckBox::create("Show AABB");
		//aabb->setPosition(sf::Vector2f(WIDTH, 100));
		//aabb->setSize("10%", "100%");
		aabb->onCheck([&](){
//        Event::Object event(Event::Object::Type::CHECKBOX_PRESSED);
//        event.checkboxPressed.id = Event::CheckboxPressed::AABB;
//        event.checkboxPressed.checked = true;
//        Event::Manager::inst().push(event);
		});
		aabb->onUncheck([&](){
//        Event::Object event(Event::Object::Type::CHECKBOX_PRESSED);
//        event.checkboxPressed.id = Event::CheckboxPressed::AABB;
//        event.checkboxPressed.checked = false;
//        Event::Manager::inst().push(event);
		});

		//layout2->add(aabb);


		//Create shapes checkbox
		shapes = tgui::CheckBox::create("Draw Shapes");
		//shapes->setSize("10%", "100%");
		//shapes->setPosition(sf::Vector2f(WIDTH, 150));
		shapes->onCheck([&](){
//        Event::Object event(Event::Object::Type::CHECKBOX_PRESSED);
//        event.checkboxPressed.id = Event::CheckboxPressed::SHAPES;
//        event.checkboxPressed.checked = true;
//        Event::Manager::inst().push(event);
		});
		shapes->onUncheck([&](){
//        Event::Object event(Event::Object::Type::CHECKBOX_PRESSED);
//        event.checkboxPressed.id = Event::CheckboxPressed::SHAPES;
//        event.checkboxPressed.checked = false;
//        Event::Manager::inst().push(event);
		});
		tgui::Panel::Ptr panel = tgui::Panel::create();
		aabb->setPosition({position1.x, position1.y});
		panel->add(aabb);
		panel->add(shapes);
		shapes->setPosition({position2.x, position2.y});
		layout2->add(panel);
        //layout2->setSize("60%", "10%");

		//Create joints checkbox
		joints = tgui::CheckBox::create("Draw Joints");
		//joints->setSize("10%", "100%");
		//joints->setPosition(sf::Vector2f(WIDTH, 200));
		joints->onCheck([&](){
//            Event::Object event(Event::Object::Type::CHECKBOX_PRESSED);
//            event.checkboxPressed.id = Event::CheckboxPressed::JOINT;
//            event.checkboxPressed.checked = true;
//            Event::Manager::inst().push(event);
		});
		joints->onCheck([&](){
//            Event::Object event(Event::Object::Type::CHECKBOX_PRESSED);
//            event.checkboxPressed.id = Event::CheckboxPressed::JOINT;
//            event.checkboxPressed.checked = false;
//            Event::Manager::inst().push(event);
		});

		//layout3->add(joints);

		//Create center of mass checkbox
		centerOfMass = tgui::CheckBox::create("Draw Mass");
		//centerOfMass->setSize("10%", "100%");
		//centerOfMass->setPosition(sf::Vector2f(WIDTH, 250));
		centerOfMass->onCheck([&](){
//            Event::Object event(Event::Object::Type::CHECKBOX_PRESSED);
//            event.checkboxPressed.id = Event::CheckboxPressed::CENTER_OF_MASS;
//            event.checkboxPressed.checked = true;
//            Event::Manager::inst().push(event);
		});
		centerOfMass->onUncheck([&](){

//            Event::Object event(Event::Object::Type::CHECKBOX_PRESSED);
//            event.checkboxPressed.id = Event::CheckboxPressed::CENTER_OF_MASS;
//            event.checkboxPressed.checked = false;
//            Event::Manager::inst().push(event);
		});

		//layout3->add(centerOfMass);

        tgui::Panel::Ptr panel2 = tgui::Panel::create();
        joints->setPosition({position1.x, position1.y});
        centerOfMass->setPosition({position2.x, position2.y});
        panel2->add(joints);
        panel2->add(centerOfMass);
        layout3->add(panel2);
		//Create pair checkbox
		pair = tgui::CheckBox::create("Draw Pairs");
		//pair->setSize("10%", "100%");
		//pair->setPosition(sf::Vector2f(WIDTH, 300));

		pair->onCheck([&](){
//            Event::Object event(Event::Object::Type::CHECKBOX_PRESSED);
//            event.checkboxPressed.id = Event::CheckboxPressed::PAIR;
//            event.checkboxPressed.checked = true;
//            Event::Manager::inst().push(event);
		});
		pair->onUncheck([&](){
//            Event::Object event(Event::Object::Type::CHECKBOX_PRESSED);
//            event.checkboxPressed.id = Event::CheckboxPressed::PAIR;
//            event.checkboxPressed.checked = false;
//            Event::Manager::inst().push(event);
		});

        tgui::Panel::Ptr panel3 = tgui::Panel::create();
        layout4->add(panel3);
		panel3->add(pair);
		pair->setPosition({position1.x, position1.y});
		tgui::Label::Ptr label = tgui::Label::create();
		label->setPosition({position2.x, position2.y});
		panel3->add(label);

	}

    void DevPanel::init(const sf::String selected, const int32 flags, const int &width, const int &height)
    {

        UNUSED(selected);
        UNUSED(flags);        
        this->setSize(width / 2, height / 2);
        this->setPosition(width / 4, height / 4);
        centerOfMass->setChecked(flags & b2Draw::e_centerOfMassBit);
        pair->setChecked(flags & b2Draw::e_centerOfMassBit);
        joints->setChecked(flags & b2Draw::e_jointBit);
        shapes->setChecked(flags & b2Draw::e_shapeBit);
        aabb->setChecked(flags & b2Draw::e_aabbBit);
//        tabs->select(selected);
    }

	DevPanel::~DevPanel()
	{

	}
}
