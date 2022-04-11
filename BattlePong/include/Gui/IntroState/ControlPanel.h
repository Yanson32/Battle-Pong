#ifndef GUI_CONTROLPANEL_H
#define GUI_CONTROLPANEL_H
#include "Gui/IntroState/OptionsPanel.h"
class DebugDraw;
namespace Gui
{
    class ControlPanel: public Gui::OptionsPanel
    {
        public:
            ControlPanel(DebugDraw *debugDraw);
            void init(const int &width, const int &height);
            virtual ~ControlPanel();
        public:
        tgui::Label::Ptr upLabel;
        tgui::ComboBox::Ptr upComboBox;
        tgui::Label::Ptr downLabel;
        tgui::ComboBox::Ptr downComboBox;
        tgui::ComboBox::Ptr rightComboBox;
        tgui::ComboBox::Ptr leftComboBox;
        tgui::ComboBox::Ptr menuComboBox;
        tgui::ComboBox::Ptr nextComboBox;
        tgui::ComboBox::Ptr selectComboBox;

        tgui::ComboBox::Ptr joystickMenuComboBox = nullptr;
        tgui::ComboBox::Ptr joystickSelectComboBox = nullptr;
        tgui::ComboBox::Ptr joystickNextComboBox = nullptr;
    };
}

#endif // GUI_CONTROLPANEL_H
