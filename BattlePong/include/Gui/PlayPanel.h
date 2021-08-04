#ifndef PLAY_PANEL_H
#define PLAY_PANEL_H

#include "Gui/CustomPanel.h"
#include <TGUI/TGUI.hpp>
class PlayPanel: public Gui::CustomPanel
{
    public:
        PlayPanel();
        void init(const int &width, const int &height);
        ~PlayPanel();
    private:
        tgui::Button::Ptr backBtn;
};
#endif
