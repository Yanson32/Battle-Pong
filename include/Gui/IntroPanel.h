#ifndef GUI_INTROPANEL_H
#define GUI_INTROPANEL_H
#include "Gui/CustomPanel.h"

namespace Gui
{
    class IntroPanel: public Gui::CustomPanel
    {
        public:
            IntroPanel();
            virtual ~IntroPanel();
        protected:
        private:
            tgui::Button::Ptr startBtn;
            tgui::Button::Ptr optionsBtn;
    };
}
#endif // GUI_INTROPANEL_H
