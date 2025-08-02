#include "Gui/OptionsPanel/ControlPanel.h"
#include "Settings.h"
#include "Macros.h"
#include "SFMLFunctions.h"
#include <sstream>
#include <SFML/Window/Joystick.hpp>
#include <GameUtilities/Core/PreferencesManager.h>
#include <GameUtilities/Core/String.h>

namespace Gui
{
    /*******************************************************************
    * @brief: Constructor
    * @param: debugDraw a pointer to the debug draw class for Box2d
    *******************************************************************/
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
            if(temp != "Error")
                upComboBox->addItem(tgui::String(temp));
        }
        upComboBox->setSelectedItem(Settings::keyboardControlUp);
        upComboBox->onItemSelect(&ControlPanel::onUpCombo, this);
        getContentPane()->append("Up", upComboBox);



        //Create down button editbox
        downComboBox = tgui::ComboBox::create();
        downComboBox->setChangeItemOnScroll(true);
        for(int i = 0; i < sf::Keyboard::Key::KeyCount; ++i)
        {
            sf::String temp = toString(static_cast<sf::Keyboard::Key>(i));
            if(temp != "Error")
                downComboBox->addItem(tgui::String(temp));
        }
        downComboBox->setSelectedItem(Settings::keyboardControlDown);
        downComboBox->onItemSelect(&ControlPanel::onDownCombo, this);
        getContentPane()->append("Down", downComboBox);

        //Create left button editbox
        leftComboBox = tgui::ComboBox::create();
        leftComboBox->setChangeItemOnScroll(true);
        for(int i = 0; i < sf::Keyboard::Key::KeyCount; ++i)
        {
            sf::String temp = toString(static_cast<sf::Keyboard::Key>(i));
            if(temp != "Error")
                leftComboBox->addItem(tgui::String(temp));
        }
        leftComboBox->setSelectedItem(Settings::keyboardControlLeft);
        leftComboBox->onItemSelect(&ControlPanel::onLeftCombo, this);
        getContentPane()->append("Left", leftComboBox);

        //Create right button editbox
        rightComboBox = tgui::ComboBox::create();
        rightComboBox->setChangeItemOnScroll(true);
        for(int i = 0; i < sf::Keyboard::Key::KeyCount; ++i)
        {
            sf::String temp = toString(static_cast<sf::Keyboard::Key>(i));
            if(temp != "Error")
                rightComboBox->addItem(tgui::String(temp));
        }
        rightComboBox->setSelectedItem(Settings::keyboardControlRight);
        rightComboBox->onItemSelect(&ControlPanel::onRightCombo, this);
        getContentPane()->append("Right", rightComboBox);


        //Create menu button editbox
        menuComboBox = tgui::ComboBox::create();
        menuComboBox->setChangeItemOnScroll(true);
        for(int i = 0; i < sf::Keyboard::Key::KeyCount; ++i)
        {
            sf::String temp = toString(static_cast<sf::Keyboard::Key>(i));
            if(temp != "Error")
                menuComboBox->addItem(tgui::String(temp));
        }
        menuComboBox->setSelectedItem(Settings::keyboardControlMenu);
        menuComboBox->onItemSelect(&ControlPanel::onMenuCombo, this);
        getContentPane()->append("Menu", menuComboBox);


        //Create next button editbox
        nextComboBox = tgui::ComboBox::create();
        nextComboBox->setChangeItemOnScroll(true);
        for(int i = 0; i < sf::Keyboard::Key::KeyCount; ++i)
        {
            sf::String temp = toString(static_cast<sf::Keyboard::Key>(i));
            if(temp != "Error")
                nextComboBox->addItem(tgui::String(temp));
        }
        nextComboBox->setSelectedItem(Settings::keyboardControlNext);
        nextComboBox->onItemSelect(&ControlPanel::onNextCombo, this);
        getContentPane()->append("Next", nextComboBox);


        //Create select button editbox
        selectComboBox = tgui::ComboBox::create();
          selectComboBox->setChangeItemOnScroll(true);
        for(int i = 0; i < sf::Keyboard::Key::KeyCount; ++i)
        {
            sf::String temp = toString(static_cast<sf::Keyboard::Key>(i));
            if(temp != "Error")
                selectComboBox->addItem(tgui::String(temp));
        }
        selectComboBox->setSelectedItem(Settings::keyboardControlSelect);
        selectComboBox->onItemSelect(&ControlPanel::onSelectCombo, this);
        getContentPane()->append("Select", selectComboBox);


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
        joystickMenuComboBox->setSelectedItem(Settings::playerJoystickControlMenu);
        joystickMenuComboBox->onItemSelect(&ControlPanel::onJoystickMenuCombo, this);
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
        joystickNextComboBox->onItemSelect(&ControlPanel::onJoystickNextCombo, this);
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
        joystickSelectComboBox->onItemSelect(&ControlPanel::onJoystickSelectCombo, this);
        if(sf::Joystick::isConnected(0))
        {
            getContentPane()->append("Select", joystickSelectComboBox);

        }

    }

    /*******************************************************************
    * @brief: Event handler for up combo box. This event handler will
    *         set the appropriate setting
    *******************************************************************/
    void ControlPanel::onUpCombo()
    {
      Settings::keyboardControlUp = this->upComboBox->getSelectedItem().toStdString();
    }


    /*******************************************************************
    * @brief: Event handler for down combo box. This event handler will
    *         set the appropriate setting
    *******************************************************************/
    void ControlPanel::onDownCombo()
    {
      Settings::keyboardControlDown = this->downComboBox->getSelectedItem().toStdString();
    }


    /*******************************************************************
    * @brief: Event handler for left combo box. This event handler will
    *         set the appropriate setting
    *******************************************************************/
    void ControlPanel::onLeftCombo()
    {
      Settings::keyboardControlLeft = this->leftComboBox->getSelectedItem().toStdString();
    }


    /*******************************************************************
    * @brief: Event handler for right combo box. This event handler will
    *         set the appropriate setting
    *******************************************************************/
    void ControlPanel::onRightCombo()
    {
      Settings::keyboardControlRight = this->rightComboBox->getSelectedItem().toStdString();
    }


    /*******************************************************************
    * @brief: Event handler for menu combo box. This event handler will
    *         set the appropriate setting
    *******************************************************************/
    void ControlPanel::onMenuCombo()
    {
        Settings::keyboardControlMenu = this->menuComboBox->getSelectedItem().toStdString();
    }


    /*******************************************************************
    * @brief: Event handler for next combo box. This event handler will
    *         set the appropriate setting
    *******************************************************************/
    void ControlPanel::onNextCombo()
    {
        Settings::keyboardControlNext = this->nextComboBox->getSelectedItem().toStdString();
    }


    /*******************************************************************
    * @brief: Event handler for select combo box. This event handler will
    *         set the appropriate setting
    *******************************************************************/
    void ControlPanel::onSelectCombo()
    {
      Settings::keyboardControlSelect = this->selectComboBox->getSelectedItem().toStdString();
    }


    /*******************************************************************
    * @brief: Event handler for joystick menu combo box. This event handler will
    *         set the appropriate setting
    *******************************************************************/
    void ControlPanel::onJoystickMenuCombo()
    {
      Settings::playerJoystickControlMenu = this->joystickMenuComboBox->getSelectedItem().toStdString();
    }


    /*******************************************************************
    * @brief: Event handler for joystick next combo box. This event handler will
    *         set the appropriate setting
    *******************************************************************/
    void ControlPanel::onJoystickNextCombo()
    {
      Settings::playerJoystickControlNext = this->joystickNextComboBox->getSelectedItem().toStdString();
    }


    /*******************************************************************
    * @brief: Event handler for joystick select combo box. This event handler will
    *         set the appropriate setting
    *******************************************************************/
    void ControlPanel::onJoystickSelectCombo()
    {
      Settings::playerJoystickControlSelect = this->joystickSelectComboBox->getSelectedItem().toStdString();
    }


    /*******************************************************************
    * @brief: This method initialized the gui
    * @param: width the horizontal size of the gui.
    * @param: height the vertical size of the gui.
    *******************************************************************/
    void ControlPanel::init(const int &width, const int &height)
    {
        tabs->select("Controls");
        this->setSize(width / 2, height / 2);
        this->setPosition(width / 4, height / 4);

    }


    /*******************************************************************
    * @brief: Destructor
    *******************************************************************/
    ControlPanel::~ControlPanel()
    {

    }
}
