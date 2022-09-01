#ifndef INTROGUI_H
#define INTROGUI_H
#include "Gui/CustomPanel.h"


namespace GU
{
    namespace Gui
    {
        class IntroPanel: public Gui::CustomPanel
        {
            public:
                IntroPanel();
                void init(const int &width, const int &height);
                virtual ~IntroPanel();
            protected:
            private:
                tgui::Button::Ptr start;
                tgui::Button::Ptr multiPlayer;
                tgui::Button::Ptr options;
                tgui::Button::Ptr credits;
        };
    }
}
#endif // INTROGUI_H
