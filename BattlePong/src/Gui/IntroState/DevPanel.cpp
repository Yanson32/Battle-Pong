#include "Gui/IntroState/DevPanel.h"
#include "Events/EventManager.h"
//#include "DebugDraw.h"
#include "Macros.h"
#include "Box2D/Box2D.h"
#include "Gui/CheckboxId.h"
#include <GameUtilities/Event/OnCheck.h>

namespace Gui
{
	DevPanel::DevPanel():
	OptionsPanel::OptionsPanel(sf::String("Dev"))
	{
        sf::Vector2f position1(75, 0);
        sf::Vector2f position2(225, 0);

        //Create header for the box2d section
        getContentPane()->appendSpace();
        getContentPane()->appendHeader("Box2d");

        //Create AABB checkbox
        aabb = tgui::CheckBox::create("");
				aabb->onCheck([&](){
	        EventManager::inst().Post<GU::Evt::OnCheck>(checkBoxId::DEBUG_AABB, true);
        });
				aabb->onUncheck([&](){
	        EventManager::inst().Post<GU::Evt::OnCheck>(checkBoxId::DEBUG_AABB, false);
				});
        getContentPane()->append("AABB", aabb);


		//Create shapes checkbox
		shapes = tgui::CheckBox::create("");
		shapes->onCheck([&](){
	        EventManager::inst().Post<GU::Evt::OnCheck>(checkBoxId::DEBUG_SHAPE, true);
		});
		shapes->onUncheck([&](){
	        EventManager::inst().Post<GU::Evt::OnCheck>(checkBoxId::DEBUG_SHAPE, false);
		});
		getContentPane()->append("Shapes", shapes);

		//Create joints checkbox
		joints = tgui::CheckBox::create("");
		joints->onCheck([&](){
	        EventManager::inst().Post<GU::Evt::OnCheck>(checkBoxId::DEBUG_JOINTS, true);
		});
		joints->onUncheck([&](){
	        EventManager::inst().Post<GU::Evt::OnCheck>(checkBoxId::DEBUG_JOINTS, false);
		});

		getContentPane()->append("Joints", joints);

		//Create center of mass checkbox
		centerOfMass = tgui::CheckBox::create("");
		centerOfMass->onCheck([&](){
	        EventManager::inst().Post<GU::Evt::OnCheck>(checkBoxId::DEBUG_MASS, true);
		});
		centerOfMass->onUncheck([&](){
	        EventManager::inst().Post<GU::Evt::OnCheck>(checkBoxId::DEBUG_MASS, false);
		});

		getContentPane()->append("Mass", centerOfMass);

		//Create pair checkbox
		pair = tgui::CheckBox::create("");
		pair->onCheck([&](){
	        EventManager::inst().Post<GU::Evt::OnCheck>(checkBoxId::DEBUG_PAIRS, true);
		});
		pair->onUncheck([&](){
	        EventManager::inst().Post<GU::Evt::OnCheck>(checkBoxId::DEBUG_PAIRS, false);
		});

		getContentPane()->append("Pairs", pair);

        getContentPane()->appendSpace();
	}

    void DevPanel::init(const int32 flags, const int &width, const int &height)
    {
        UNUSED(flags);
        this->setSize(width / 2, height / 2);
        this->setPosition(width / 4, height / 4);
        centerOfMass->setChecked(flags & b2Draw::e_centerOfMassBit);
        pair->setChecked(flags & b2Draw::e_centerOfMassBit);
        joints->setChecked(flags & b2Draw::e_jointBit);
        shapes->setChecked(flags & b2Draw::e_shapeBit);
        aabb->setChecked(flags & b2Draw::e_aabbBit);
    }

	DevPanel::~DevPanel()
	{

	}
}
