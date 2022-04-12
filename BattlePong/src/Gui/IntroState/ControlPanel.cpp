#include "Gui/IntroState/ControlPanel.h"
#include "Settings.h"
#include "Macros.h"
#include "SFMLFunctions.h"
#include <sstream>
#include <SFML/Window/Joystick.hpp>
#include <GameUtilities/Core/PreferencesManager.h>
#include <GameUtilities/Core/String.h>

namespace Gui
{
    ControlPanel::ControlPanel(DebugDraw *debugDraw):
    OptionsPanel::OptionsPanel("Controls")
    {
        UNUSED(debugDraw);

        getContentPane()->appendSpace();

        //Create header for the keyboard section
        getContentPane()->appendHeader("Keyboard");

        //Create up button editbox
        upComboBox = tgui::ComboBox::create();
	    upComboBox->setChangeItemOnScroll(true);
        for(int i = 0; i < sf::Keyboard::Key::KeyCount; ++i)
        {
            sf::String temp = toString(static_cast<sf::Keyboard::Key>(i));
            upComboBox->addItem(tgui::String(temp));
        }
        upComboBox->setSelectedItem(Settings::playerControlUp);
        getContentPane()->append("Up", upComboBox);


        upComboBox->onItemSelect([this](){
          GU::Core::String data = this->upComboBox->getSelectedItem().toStdString();
          //Load user preferences
          GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
          prefMan.write("PlayerControlUp", data);

        });

        //Create down button editbox
        downComboBox = tgui::ComboBox::create();
	    downComboBox->setChangeItemOnScroll(true);
        for(int i = 0; i < sf::Keyboard::Key::KeyCount; ++i)
        {
            sf::String temp = toString(static_cast<sf::Keyboard::Key>(i));
            downComboBox->addItem(tgui::String(temp));
        }
        downComboBox->setSelectedItem(Settings::playerControlDown);
	      getContentPane()->append("Down", downComboBox);
        downComboBox->onItemSelect([this](){
          GU::Core::String data = this->downComboBox->getSelectedItem().toStdString();
          //Load user preferences
          GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
          prefMan.write("PlayerControlDown", data);

        });

        //Create left button editbox
        leftComboBox = tgui::ComboBox::create();
	    leftComboBox->setChangeItemOnScroll(true);
        for(int i = 0; i < sf::Keyboard::Key::KeyCount; ++i)
        {
            sf::String temp = toString(static_cast<sf::Keyboard::Key>(i));
            leftComboBox->addItem(tgui::String(temp));
        }
        leftComboBox->setSelectedItem(Settings::playerControlLeft);
	    getContentPane()->append("Left", leftComboBox);

      leftComboBox->onItemSelect([this](){
        GU::Core::String data = this->leftComboBox->getSelectedItem().toStdString();
        //Load user preferences
        GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
        prefMan.write("PlayerControlLeft", data);

      });
        //Create right button editbox
        rightComboBox = tgui::ComboBox::create();
	    rightComboBox->setChangeItemOnScroll(true);
        for(int i = 0; i < sf::Keyboard::Key::KeyCount; ++i)
        {
            sf::String temp = toString(static_cast<sf::Keyboard::Key>(i));
            rightComboBox->addItem(tgui::String(temp));
        }
        rightComboBox->setSelectedItem(Settings::playerControlRight);
	      getContentPane()->append("Right", rightComboBox);

        rightComboBox->onItemSelect([this](){
        GU::Core::String data = this->rightComboBox->getSelectedItem().toStdString();
        //Load user preferences
        GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
        prefMan.write("PlayerControlRight", data);

      });

        //Create menu button editbox
        menuComboBox = tgui::ComboBox::create();
	    menuComboBox->setChangeItemOnScroll(true);
        for(int i = 0; i < sf::Keyboard::Key::KeyCount; ++i)
        {
            sf::String temp = toString(static_cast<sf::Keyboard::Key>(i));
            menuComboBox->addItem(tgui::String(temp));
        }
        menuComboBox->setSelectedItem(Settings::playerControlMenu);
	    getContentPane()->append("Menu", menuComboBox);

      menuComboBox->onItemSelect([this](){
      GU::Core::String data = this->menuComboBox->getSelectedItem().toStdString();
      //Load user preferences
      GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
      prefMan.write("PlayerControlMenu", data);

    });

        //Create next button editbox
        nextComboBox = tgui::ComboBox::create();
	    nextComboBox->setChangeItemOnScroll(true);
        for(int i = 0; i < sf::Keyboard::Key::KeyCount; ++i)
        {
            sf::String temp = toString(static_cast<sf::Keyboard::Key>(i));
            nextComboBox->addItem(tgui::String(temp));
        }
        nextComboBox->setSelectedItem(Settings::playerControlNext);
	    getContentPane()->append("Next", nextComboBox);

      nextComboBox->onItemSelect([this](){
      GU::Core::String data = this->nextComboBox->getSelectedItem().toStdString();
      //Load user preferences
      GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
      prefMan.write("PlayerControlNext", data);

    });

        //Create select button editbox
        selectComboBox = tgui::ComboBox::create();
	    selectComboBox->setChangeItemOnScroll(true);
        for(int i = 0; i < sf::Keyboard::Key::KeyCount; ++i)
        {
            sf::String temp = toString(static_cast<sf::Keyboard::Key>(i));
            selectComboBox->addItem(tgui::String(temp));
        }
        selectComboBox->setSelectedItem(Settings::playerControlSelect);
	    getContentPane()->append("Select", selectComboBox);

      selectComboBox->onItemSelect([this](){
      GU::Core::String data = this->selectComboBox->getSelectedItem().toStdString();
      //Load user preferences
      GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
      prefMan.write("PlayerControlSelect", data);

    });
        //Create joystick section
        if(sf::Joystick::isConnected(0))
            getContentPane()->appendHeader("Joystick");


        //Create menu button editbox
        joystickMenuComboBox = tgui::ComboBox::create();
	    joystickMenuComboBox->setChangeItemOnScroll(true);
        for(unsigned int i = 0; i < sf::Joystick::getButtonCount(0); ++i)
        {
            std::stringstream ss;
            ss << "Button ";
            ss << i;
            joystickMenuComboBox->addItem(ss.str());
        }
        joystickMenuComboBox->setSelectedItem(Settings::playerControlMenu);
        if(sf::Joystick::isConnected(0))
        {
	        getContentPane()->append("Menu", joystickMenuComboBox);
        }

        //Create joystick next button editbox
        joystickNextComboBox = tgui::ComboBox::create();
        joystickNextComboBox->setChangeItemOnScroll(true);
        for(unsigned int i = 0; i < sf::Joystick::getButtonCount(0); ++i)
        {
            std::stringstream ss;
            ss << "Button ";
            ss << i;
            joystickNextComboBox->addItem(ss.str());
        }
        joystickNextComboBox->setSelectedItem(Settings::playerJoystickControlNext);
        if(sf::Joystick::isConnected(0))
        {
            getContentPane()->append("Next", joystickNextComboBox);
        }

        //Create joystick select button editbox
        joystickSelectComboBox = tgui::ComboBox::create();
        joystickSelectComboBox->setChangeItemOnScroll(true);
        for(unsigned int i = 0; i < sf::Joystick::getButtonCount(0); ++i)
        {
            std::stringstream ss;
            ss << "Button ";
            ss << i;
            joystickSelectComboBox->addItem(ss.str());
        }
        joystickSelectComboBox->setSelectedItem(Settings::playerJoystickControlSelect);
        if(sf::Joystick::isConnected(0))
        {
            getContentPane()->append("Select", joystickSelectComboBox);

        }
    }

    void ControlPanel::init(const int &width, const int &height)
    {
        tabs->select("Controls");
        this->setSize(width / 2, height / 2);
        this->setPosition(width / 4, height / 4);

    }
    ControlPanel::~ControlPanel()
    {

    }
}
