#ifndef GUI_GENERALPANEL_H
#define GUI_GENERALPANEL_H
#include "Gui/IntroState/OptionsPanel.h"
#include "Settings.h"
#include "States/StateId.h"

class DebugDraw;
namespace Gui
{
    class GeneralPanel: public OptionsPanel
    {
        public:
            GeneralPanel(const StateId state = Settings::stateId);
            void init(const int &width, const int &height);
            virtual ~GeneralPanel();
        protected:
            tgui::ComboBox::Ptr comboBox;
            tgui::Label::Ptr comboLable;

            tgui::ComboBox::Ptr aiCombo;
            tgui::Label::Ptr aiLable;
    };
}

#endif // GUI_GENERALPANEL_H
