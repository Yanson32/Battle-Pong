#ifndef GUI_GENERALPANEL_H
#define GUI_GENERALPANEL_H
#include "Gui/OptionsPanel.h"
class DebugDraw;
namespace Gui
{
    class GeneralPanel: public OptionsPanel
    {
        public:
            GeneralPanel(DebugDraw *debugDraw);
            void init();
            virtual ~GeneralPanel();
        protected:
            tgui::ComboBox::Ptr comboBox;
            tgui::Label::Ptr comboLable;

            tgui::ComboBox::Ptr aiCombo;
            tgui::Label::Ptr aiLable;
    };
}

#endif // GUI_GENERALPANEL_H
