#ifndef INTROGUI_H
#define INTROGUI_H
#include "Gui/CustomPanel.h"

class InfoPanel: public Gui::CustomPanel
{
    public:
        InfoPanel();
        void init(const int &width, const int &height);
        virtual ~InfoPanel();
    protected:
    private:
        tgui::Button::Ptr start;
        tgui::Button::Ptr multiPlayer;
        tgui::Button::Ptr options;
        tgui::Button::Ptr credits;
};

#endif // INTROGUI_H
