#ifndef HOST_PANEL_H
#define HOST_PANEL_H

#include "Gui/CustomPanel.h"
#include <TGUI/TGUI.hpp>
class HostPanel: public Gui::CustomPanel
{
    public:
        HostPanel();
        ~HostPanel();
    private:
        tgui::Button::Ptr backBtn;
        tgui::Label::Ptr portLabel;
        tgui::EditBox::Ptr portBox;
        tgui::Button::Ptr hostButton;
};
#endif
