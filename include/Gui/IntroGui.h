#ifndef INTROGUI_H
#define INTROGUI_H
#include "Gui/CustomPanel.h"

class IntroGui: public Gui::CustomPanel
{
    public:
        IntroGui();
        virtual ~IntroGui();
    protected:
    private:
        tgui::Button::Ptr start;
        tgui::Button::Ptr multiPlayer;
        tgui::Button::Ptr options;
};

#endif // INTROGUI_H
