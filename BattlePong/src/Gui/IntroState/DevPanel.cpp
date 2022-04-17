#include "Gui/IntroState/DevPanel.h"
#include "Events/EventManager.h"
//#include "DebugDraw.h"
#include "Macros.h"
#include "Box2D/Box2D.h"
#include "Gui/CheckboxId.h"
#include <GameUtilities/Event/OnCheck.h>
#include <GameUtilities/Log/LogType.h>
#include <GameUtilities/Core/PreferencesManager.h>
#include "Settings.h"
#include <iostream>

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


		//Create header for the box2d section
		getContentPane()->appendHeader("Log");

		//Create Log checkbox
		log = tgui::EditBox::create();
		log->setText(Settings::preferencesFile);

		getContentPane()->append("Log File", log);

		//Create menu button editbox
		logLevelComboBox = tgui::ComboBox::create();
		logLevelComboBox->setChangeItemOnScroll(true);
		logLevelComboBox->addItem(tgui::String("Fatal Error"));
		logLevelComboBox->addItem(tgui::String("Error"));
		logLevelComboBox->addItem(tgui::String("Warning"));
		logLevelComboBox->addItem(tgui::String("Message"));
		logLevelComboBox->addItem(tgui::String("Verbose"));
		logLevelComboBox->addItem(tgui::String("Status"));
		logLevelComboBox->addItem(tgui::String("Debug"));
		logLevelComboBox->addItem(tgui::String("Trace"));
		switch(static_cast<GU::Log::LogType>(Settings::logSeverity))
		{
			case GU::Log::LogType::GU_FATAL_ERROR:
				logLevelComboBox->setSelectedItem("Fatal Error");
			break;
			case GU::Log::LogType::GU_ERROR:
				logLevelComboBox->setSelectedItem("Error");
			break;
			case GU::Log::LogType::GU_WARNING:
				logLevelComboBox->setSelectedItem("Warning");
			break;
			case GU::Log::LogType::GU_MESSAGE:
				logLevelComboBox->setSelectedItem("Message");
			break;
			case GU::Log::LogType::GU_VERBOSE:
				logLevelComboBox->setSelectedItem("Verbose");
			break;
			case GU::Log::LogType::GU_STATUS:
				logLevelComboBox->setSelectedItem("Status");
			break;
			case GU::Log::LogType::GU_DEBUG:
				logLevelComboBox->setSelectedItem("Debug");
			break;
			case GU::Log::LogType::GU_TRACE:
				logLevelComboBox->setSelectedItem("Trace");
			break;
		}

		getContentPane()->append("Severity", logLevelComboBox);
		logLevelComboBox->onItemSelect(&DevPanel::onLogLevel, this);
	}

    void DevPanel::init(const int32 flags, const int &width, const int &height)
    {
        UNUSED(flags);
        this->setSize(width / 2, height / 2);
        this->setPosition(width / 4, height / 4);
        centerOfMass->setChecked(Settings::b2centerOfMass);
        pair->setChecked(Settings::b2pair);
        joints->setChecked(Settings::b2joints);
        shapes->setChecked(Settings::b2shapes);
        aabb->setChecked(Settings::b2aabb);
    }

	void DevPanel::onLogLevel()
	{
		GU::Core::String data = this->logLevelComboBox->getSelectedItem().toStdString();
		//Load user preferences
		GU::Core::PreferencesManager prefMan(Settings::preferencesFile);

		if(data == GU::Core::String("Fatal Error"))
		{
			prefMan.write("LogSeverity", static_cast<int>(GU::Log::LogType::GU_FATAL_ERROR));
			Settings::logSeverity = static_cast<int>(GU::Log::LogType::GU_FATAL_ERROR);
		}
		else if(data == GU::Core::String("Error"))
		{
			prefMan.write("LogSeverity", static_cast<int>(GU::Log::LogType::GU_ERROR));
			Settings::logSeverity = static_cast<int>(GU::Log::LogType::GU_ERROR);
		}
		else if(data == GU::Core::String("Warning"))
		{
			prefMan.write("LogSeverity", static_cast<int>(GU::Log::LogType::GU_WARNING));
			Settings::logSeverity = static_cast<int>(GU::Log::LogType::GU_WARNING);
		}
		else if(data == GU::Core::String("Message"))
		{
			prefMan.write("LogSeverity", static_cast<int>(GU::Log::LogType::GU_MESSAGE));
			Settings::logSeverity = static_cast<int>(GU::Log::LogType::GU_MESSAGE);
		}
		else if(data == GU::Core::String("Verbose"))
		{
			prefMan.write("LogSeverity", static_cast<int>(GU::Log::LogType::GU_VERBOSE));
			Settings::logSeverity = static_cast<int>(GU::Log::LogType::GU_VERBOSE);
		}
		else if(data == GU::Core::String("Status"))
		{
			prefMan.write("LogSeverity", static_cast<int>(GU::Log::LogType::GU_STATUS));
			Settings::logSeverity = static_cast<int>(GU::Log::LogType::GU_STATUS);
		}
		else if(data == GU::Core::String("Debug"))
		{
			prefMan.write("LogSeverity", static_cast<int>(GU::Log::LogType::GU_DEBUG));
			Settings::logSeverity = static_cast<int>(GU::Log::LogType::GU_DEBUG);
		}
		else if(data == GU::Core::String("Trace"))
		{
			prefMan.write("LogSeverity", static_cast<int>(GU::Log::LogType::GU_TRACE));
			Settings::logSeverity = static_cast<int>(GU::Log::LogType::GU_TRACE);
		}
	}


	DevPanel::~DevPanel()
	{

	}
}
