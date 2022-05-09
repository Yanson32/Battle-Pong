#ifndef GUI_CONTROLPANEL_H
#define GUI_CONTROLPANEL_H
#include "Gui/OptionsPanel/OptionsPanel.h"
class DebugDraw;
namespace Gui
{
    class ControlPanel: public Gui::OptionsPanel
    {
        public:
            /*******************************************************************
            * @brief: Constructor
            * @param: debugDraw a pointer to the debug draw class for Box2d
            *******************************************************************/
            ControlPanel(DebugDraw *debugDraw);


            /*******************************************************************
            * @brief: This method initialized the gui
            * @param: width the horizontal size of the gui.
            * @param: height the vertical size of the gui.
            *******************************************************************/
            void init(const int &width, const int &height);


            /*******************************************************************
            * @brief: Destructor
            *******************************************************************/
            virtual ~ControlPanel();
        private:
            /*******************************************************************
            * @brief: Event handler for up combo box. This event handler will
            *         set the appropriate setting
            *******************************************************************/
            void onUpCombo();


            /*******************************************************************
            * @brief: Event handler for down combo box. This event handler will
            *         set the appropriate setting
            *******************************************************************/
            void onDownCombo();


            /*******************************************************************
            * @brief: Event handler for left combo box. This event handler will
            *         set the appropriate setting
            *******************************************************************/
            void onLeftCombo();


            /*******************************************************************
            * @brief: Event handler for right combo box. This event handler will
            *         set the appropriate setting
            *******************************************************************/
            void onRightCombo();


            /*******************************************************************
            * @brief: Event handler for menu combo box. This event handler will
            *         set the appropriate setting
            *******************************************************************/
            void onMenuCombo();


            /*******************************************************************
            * @brief: Event handler for next combo box. This event handler will
            *         set the appropriate setting
            *******************************************************************/
            void onNextCombo();


            /*******************************************************************
            * @brief: Event handler for select combo box. This event handler will
            *         set the appropriate setting
            *******************************************************************/
            void onSelectCombo();


            /*******************************************************************
            * @brief: Event handler for joystick menu combo box. This event handler will
            *         set the appropriate setting
            *******************************************************************/
            void onJoystickMenuCombo();


            /*******************************************************************
            * @brief: Event handler for joystick next combo box. This event handler will
            *         set the appropriate setting
            *******************************************************************/
            void onJoystickNextCombo();


            /*******************************************************************
            * @brief: Event handler for joystick select combo box. This event handler will
            *         set the appropriate setting
            *******************************************************************/
            void onJoystickSelectCombo();


            //Keyboard
            tgui::Label::Ptr upLabel;
            tgui::ComboBox::Ptr upComboBox;
            tgui::Label::Ptr downLabel;
            tgui::ComboBox::Ptr downComboBox;
            tgui::ComboBox::Ptr rightComboBox;
            tgui::ComboBox::Ptr leftComboBox;
            tgui::ComboBox::Ptr menuComboBox;
            tgui::ComboBox::Ptr nextComboBox;
            tgui::ComboBox::Ptr selectComboBox;

            //Joystick
            tgui::ComboBox::Ptr joystickMenuComboBox = nullptr;
            tgui::ComboBox::Ptr joystickSelectComboBox = nullptr;
            tgui::ComboBox::Ptr joystickNextComboBox = nullptr;
    };
}

#endif // GUI_CONTROLPANEL_H
